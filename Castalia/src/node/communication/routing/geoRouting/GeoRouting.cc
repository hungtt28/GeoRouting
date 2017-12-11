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

#include "GeoRouting.h"

Define_Module(GeoRouting);

//================================================================
//    startup
//================================================================
void GeoRouting::startup(){

	isCoordinateSet = false;
    
    helloInterval = (double)par("helloInterval") / 1000.0;
    activeRouteTimeout = (double)par("activeRouteTimeout") / 1000.0;
    packetsPerNode = par("packetsPerNode");
	seqHello = par("seqHello");
	
	neighborTable = new NeighborTable();
	geoProtocol = getGeoProtocol(par("protocolName"));
	geoProtocol->setProtocolMode(par("protocolMode"));
	geoProtocol->setGeoRouting(this);
	geoProtocol->initialize();
	
	declareOutput("GPSR Packets received");
	declareOutput("GPSR Packets sent");
	declareOutput("GPSR Packets forwarded");

	// we will only send HELLO message if the node's coordinates are set
}

//================================================================
//    timerFiredCallback
//================================================================
void GeoRouting::timerFiredCallback(int index){

	switch(index){
		case GEO_HELLO_MSG_REFRESH_TIMER :{
			sendHelloMessage();
			break;
		}
		
		default: {
			geoProtocol->processTimerCallback(index);
			break;
		}
	}
}


/*
handleNetworkControlCommand interface handle NETWORK_CONTROL_COMMAND from Application Layer
*/
void GeoRouting::handleNetworkControlCommand(cMessage *msg) {

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

void GeoRouting::processBufferedPacket(){
	while (!TXBuffer.empty()) {
		toMacLayer(TXBuffer.front(), BROADCAST_MAC_ADDRESS);
		TXBuffer.pop();
	}
}

//================================================================
//    fromApplicationLayer
//================================================================
void GeoRouting::fromApplicationLayer(cPacket * pkt, const char *destination){  

	GeoRoutingPacket *dataPacket = geoProtocol->createGeoRoutingPacket();
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

	geoProtocol->forwardDataPacket(dataPacket);
	delete dataPacket;
	return;
}

//================================================================
//    fromMacLayer
//================================================================
void GeoRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi){
	
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
			
			GeoRoutingPacket *routingPacket = dynamic_cast <GeoRoutingPacket*>(pkt);
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
				geoProtocol->forwardDataPacket(routingPacket);
			}
			break;
		}

		// process control packet
		case GEO_CONTROL_PACKET: {
			GeoControlPacket *controlPacket = dynamic_cast <GeoControlPacket*>(pkt);
			geoProtocol->processControlPacket(controlPacket);
			break;
		}
		
        default: return;
	}
}

//================================================================
//    finishSpecific
//================================================================
void GeoRouting::finishSpecific() {

}

//================================================================
//    sendHelloMsg
//================================================================
void GeoRouting::sendHelloMessage(){
	
    GeoBeaconPacket *helloMsg = new GeoBeaconPacket("Geo hello message packet", NETWORK_LAYER_PACKET);
    helloMsg->setSource(SELF_NETWORK_ADDRESS);
	helloMsg->setNodeLocation(nodeLocation);
    toMacLayer(helloMsg, BROADCAST_MAC_ADDRESS);
	
	seqHello++;
	setTimer(GEO_HELLO_MSG_REFRESH_TIMER, helloInterval);
	
	return;
}

void GeoRouting::sendToNextHop(GeoPacket* dataPacket, int nextHop) {
	// send packet to nexthop
	string destination(dataPacket->getDestination());
	string source(dataPacket->getSource());
	if (nextHop != -1) {
		trace() << setw(10) << "SEND" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination << "currentHop " << setw(10) << SELF_NETWORK_ADDRESS << "nextHop " << setw(10) << nextHop;
		dataPacket->setSourceId(atoi(SELF_NETWORK_ADDRESS));
		toMacLayer(dataPacket, nextHop);
    }
	else {
		trace() << setw(10) << "DROP" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination;
		delete dataPacket;
    }
	
	return;
}