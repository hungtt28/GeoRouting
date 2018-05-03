
/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GEARRouting.h"

Define_Module(GEARRouting);

//================================================================
//    startup
//================================================================
void GEARRouting::startup(){

	isCoordinateSet = false;
    
    helloInterval = (double)par("helloInterval") / 1000.0;
    activeRouteTimeout = (double)par("activeRouteTimeout") / 1000.0;
    packetsPerNode = par("packetsPerNode");
	seqHello = par("seqHello");
	
	// initialize
	range = 40;
	curId = atoi(SELF_NETWORK_ADDRESS);
	learnedCost = 0;
	alpha = 1;
	consumedEnergy = 0;

	neighborTable = new NeighborTable();
	
	declareOutput("GPSR Packets received");
	declareOutput("GPSR Packets sent");
	declareOutput("GPSR Packets forwarded");

	// we will only send HELLO message if the node's coordinates are set
}

//================================================================
//    timerFiredCallback
//================================================================
void GEARRouting::timerFiredCallback(int index){

	switch(index){
		case GEAR_HELLO_MSG_REFRESH_TIMER :{
			sendHelloMessage();
			break;
		}
		
		default: {
			break;
		}
	}
}


/*
handleNetworkControlCommand interface handle NETWORK_CONTROL_COMMAND from Application Layer
*/
void GEARRouting::handleNetworkControlCommand(cMessage *msg) {

	GeoRoutingControl *cmd = check_and_cast <GeoRoutingControl*>(msg);

	switch (cmd->getGeoRoutingCommand()) {

		case SET_GEO_NODE_POS: {
			curLocation.x = cmd->getNodeLocation().x;
			curLocation.y = cmd->getNodeLocation().y;
			isCoordinateSet = true;
			
			// normally, this is the first HELLO message
			if (isCoordinateSet) {
				  sendHelloMessage();
			}
			break;
		}
	}
}

//================================================================
//    processBufferedPacket
//================================================================

// void GEARRouting::processBufferedPacket(){
	// while (!TXBuffer.empty()) {
		// toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		// TXBuffer.pop();
	// }
// }

//================================================================
//    fromApplicationLayer
//================================================================
void GEARRouting::fromApplicationLayer(cPacket * pkt, const char *destination){  

	GEARRoutingPacket *dataPacket = new GEARRoutingPacket("GEAR routing data packet", NETWORK_LAYER_PACKET);
	GeoApplicationPacket *appPacket = check_and_cast <GeoApplicationPacket*>(pkt);
	NodeLocation_type desLocation = appPacket->getDestinationLocation();

	encapsulatePacket(dataPacket, pkt);
	dataPacket->setSource(SELF_NETWORK_ADDRESS);
	dataPacket->setDestination(destination);
	dataPacket->setDestinationLocation(desLocation);

	if (string(destination).compare(BROADCAST_NETWORK_ADDRESS)==0) {
		// if broadcast, just give it to MAC layer
		toMacLayer(dataPacket, BROADCAST_MAC_ADDRESS);
		return;
    }

	forwardDataPacket(dataPacket);
	delete dataPacket;
	return;
}

//================================================================
//    fromMacLayer
//================================================================
void GEARRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi){
	
    GeoPacket *netPacket = dynamic_cast <GeoPacket*>(pkt);

	if (!netPacket)
		return;
	
	switch (netPacket->getGeoPacketType()) {
 
        // process hello msg
		case GEO_BEACON_PACKET: {
			
			GEARHelloPacket *beaconPacket = dynamic_cast <GEARHelloPacket*>(pkt);

			int recordIndex = neighborTable->getNeighborIndex(atoi(netPacket->getSource()));
			if (recordIndex == -1) {
				NeighborRecord *neighborRecord = new NeighborRecord(atoi(netPacket->getSource()), beaconPacket->getNodeLocation());
				neighborRecord->setLearnedCost(beaconPacket->getLearnedCost());
				neighborTable->update(neighborRecord);
			}
			else {
				NeighborRecord *neighborRecord = neighborTable->getRecord(recordIndex);
				neighborRecord->setLearnedCost(beaconPacket->getLearnedCost());
				neighborRecord->setNodeLocation(beaconPacket->getNodeLocation());
			}

			break;
		}
        
        // process data packet
		case GEO_ROUTING_PACKET:
		{
			GEARRoutingPacket *routingPacket = dynamic_cast <GEARRoutingPacket*>(pkt);
			string destination(routingPacket->getDestination());
			string source(routingPacket->getSource());

			trace() << setw(10) << "RECEIVE" << "PACKET #" << setw(10) << routingPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination << "currentHop " << setw(10) << SELF_NETWORK_ADDRESS << "previousHop " << setw(10) << macAddress;

			if ((destination.compare(SELF_NETWORK_ADDRESS) == 0)) {
				trace() << setw(10) << "COMPLETE" << "PACKET #" << setw(10) << routingPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination;
				toApplicationLayer(routingPacket->decapsulate());
			} 
			else if ((destination.compare(BROADCAST_NETWORK_ADDRESS) == 0)) {
				toApplicationLayer(routingPacket->decapsulate());
			}
			else {
				forwardDataPacket(routingPacket);
			}
			break;
		}
		
        default: return;
	}
}

//================================================================
//    finishSpecific
//================================================================
void GEARRouting::finishSpecific() {

}

//================================================================
//    sendHelloMsg
//================================================================
void GEARRouting::sendHelloMessage(){
	
    GEARHelloPacket *helloMsg = new GEARHelloPacket("GEAR hello message packet", NETWORK_LAYER_PACKET);
    helloMsg->setSource(SELF_NETWORK_ADDRESS);
	helloMsg->setNodeLocation(curLocation);
	helloMsg->setLearnedCost(learnedCost);
    toMacLayer(helloMsg, BROADCAST_MAC_ADDRESS);
	
	seqHello++;
	setTimer(GEAR_HELLO_MSG_REFRESH_TIMER, helloInterval);
	
	return;
}

void GEARRouting::forwardDataPacket(GEARRoutingPacket* pkt) 
{	
	GEARRoutingPacket *dataPacket = pkt->dup();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();

	// update currently learnedCost
	if (!learnedCost)
		learnedCost = alpha * distance(curLocation, desLocation) + (1 - alpha) * consumedEnergy;

	int nextHop = findGearRoutingNextHop(dataPacket);
	
	sendToNextHop(dataPacket, nextHop);

	return;
}

void GEARRouting::sendToNextHop(GeoPacket* dataPacket, int nextHop) {
	
	// send packet to nexthop
	string destination(dataPacket->getDestination());
	string source(dataPacket->getSource());
	if (nextHop != -1) {
		trace() << setw(10) << "SEND" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination << "currentHop " << setw(10) << SELF_NETWORK_ADDRESS << "nextHop " << setw(10) << nextHop;
		
		toMacLayer(dataPacket, nextHop);
    }
	else {
		trace() << setw(10) << "DROP" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination;
		delete dataPacket;
    }
	
	return;
}

int GEARRouting::findGearRoutingNextHop(GEARRoutingPacket* dataPacket) 
{	
	int nextHop = -1;
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	double minDist = learnedCost;
	
	int indexRecord = findLowestLearnedCost(desLocation, minDist);

	// gear
	if (indexRecord == -1) 
	{
		// find lowest learnedcost among neighbors
		indexRecord = findLowestLearnedCost(desLocation, 0xffffffff);

		// gear - update learnedCost
		double toNeighborCost = distance(curLocation, neighborTable->getRecord(indexRecord)->getNodeLocation());
		learnedCost = neighborTable->getRecord(indexRecord)->getLearnedCost() + toNeighborCost;
	}
	
	if (indexRecord > -1)
		nextHop = neighborTable->getRecord(indexRecord)->getId();

	return nextHop;
}

int GEARRouting::findLowestLearnedCost(NodeLocation_type desLocation, double minCost) 
{
	int indexRecord = -1;

	// greedy
	for (int i = 0; i < neighborTable->size(); i++) {
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		double dist = neighborRecord->getLearnedCost();
		if (!dist)
			dist = distance(neighborRecord->getNodeLocation(), desLocation);
		// trace() << "[+] id " << curId << " " << neighborRecord->getId() << " " << distance(neighborRecord->getNodeLocation(), desLocation) << " " << neighborRecord->getLearnedCost();
		if (dist - minCost < ZERO) {
			indexRecord = i;
			minCost = dist;
		}
	}

	return indexRecord;
}