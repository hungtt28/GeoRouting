/*********************************************************/
/*  Copyright (c) 2011. University of Pau, France        */
/*  LIUPPA Laboratory, T2I Team                          */
/*                                                       */
/*  Permission to use, copy, modify and distribute this  */
/*  code, without fee, and without written agreement is  */
/*  hereby granted, provided that the above copyright    */
/*  notice and the authors appear in all copies          */
/*                                                       */
/*  GPSR Routing Protocol                                */
/*  Version:  1.0                                        */
/*  Authors: Diop Mamour <serignemamour.diop@gmail.com>  */
/*           Congduc Pham <congduc.pham@univ-pau.fr>     */
/*********************************************************/

/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GreedyRouting.h"

Define_Module(GreedyRouting);

//================================================================
//    startup
//================================================================
void GreedyRouting::startup(){

	isCoordinateSet = false;
    
    helloInterval = (double)par("helloInterval") / 1000.0;
    activeRouteTimeout = (double)par("activeRouteTimeout") / 1000.0;
    packetsPerNode = par("packetsPerNode");
	seqHello = par("seqHello");
	
	neighborTable = new NeighborTable();
	
	declareOutput("GPSR Packets received");
	declareOutput("GPSR Packets sent");
	declareOutput("GPSR Packets forwarded");

	// we will only send HELLO message if the node's coordinates are set
}

//================================================================
//    timerFiredCallback
//================================================================
void GreedyRouting::timerFiredCallback(int index){

	switch(index){
		case GREEDY_HELLO_MSG_REFRESH_TIMER :{
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
void GreedyRouting::handleNetworkControlCommand(cMessage *msg) {

	GeoRoutingControl *cmd = check_and_cast <GeoRoutingControl*>(msg);

	switch (cmd->getGeoRoutingCommand()) {

		case SET_GEO_NODE_POS: {
			nodeLocation.x = cmd->getNodeLocation().x;
			nodeLocation.y = cmd->getNodeLocation().y;
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

// void GreedyRouting::processBufferedPacket(){
	// while (!TXBuffer.empty()) {
		// toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		// TXBuffer.pop();
	// }
// }

//================================================================
//    fromApplicationLayer
//================================================================
void GreedyRouting::fromApplicationLayer(cPacket * pkt, const char *destination){  

	GreedyRoutingPacket *dataPacket = new GreedyRoutingPacket("Greedy routing data packet", NETWORK_LAYER_PACKET);
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
void GreedyRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi){
	
    GeoPacket *netPacket = dynamic_cast <GeoPacket*>(pkt);

	if (!netPacket)
		return;
	
	switch (netPacket->getGeoPacketType()) {
 
        // process hello msg
		case GEO_BEACON_PACKET: {
			
			GeoBeaconPacket *beaconPacket = dynamic_cast <GeoBeaconPacket*>(pkt);

			NeighborRecord *neighborRecord = new NeighborRecord(atoi(netPacket->getSource()), beaconPacket->getNodeLocation());
			neighborTable->update(neighborRecord);
			break;
		}
        
        // process data packet
		case GEO_ROUTING_PACKET:{
			
			GreedyRoutingPacket *routingPacket = dynamic_cast <GreedyRoutingPacket*>(pkt);
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
void GreedyRouting::finishSpecific() {

}

//================================================================
//    sendHelloMsg
//================================================================
void GreedyRouting::sendHelloMessage(){
	
    GeoBeaconPacket *helloMsg = new GeoBeaconPacket("Geo hello message packet", NETWORK_LAYER_PACKET);
    helloMsg->setSource(SELF_NETWORK_ADDRESS);
	helloMsg->setNodeLocation(nodeLocation);
    toMacLayer(helloMsg, BROADCAST_MAC_ADDRESS);
	
	seqHello++;
	setTimer(GREEDY_HELLO_MSG_REFRESH_TIMER, helloInterval);
	
	return;
}

void GreedyRouting::forwardDataPacket(GreedyRoutingPacket* pkt) {
	
	GreedyRoutingPacket *dataPacket = pkt->dup();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	int nextHop = -1;
	double dist = -1;
	double minDist = distance(nodeLocation, desLocation);
	
	// greedy
	for (int i = 0; i < neighborTable->size(); i++) {
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		dist = distance(neighborRecord->getNodeLocation(), desLocation);
		if (dist < minDist) {
			minDist = dist;
			nextHop = neighborRecord->getId();
		}
	}
	
	sendToNextHop(dataPacket, nextHop);
	
	return;
}

void GreedyRouting::sendToNextHop(GeoPacket* dataPacket, int nextHop) {
	
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
