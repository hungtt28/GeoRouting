/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GeoProtocol.h"
#include "GeoRouting.h"

GeoRoutingPacket* GeoProtocol::createGeoRoutingPacket() {
	return new GeoRoutingPacket("GEO routing data packet", NETWORK_LAYER_PACKET);
}

std::tuple<int, GeoRoutingPacket*> GeoProtocol::findNextHop(GeoRoutingPacket* pkt) {
	
	GeoRoutingPacket *dataPacket = pkt->dup();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	int nextHop = -1;
	double dist = -1;
	double minDist = distance(routing->getCurLocation(), desLocation);
	
	NeighborTable *neighborTable = routing->getNeighborTable();
	for (int i = 0; i < neighborTable->size(); i++) {
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		dist = distance(neighborRecord->getNodeLocation(), desLocation);
		if (dist < minDist) {
			minDist = dist;
			nextHop = neighborRecord->getId();
		}
	}
	return std::make_tuple(nextHop, dataPacket);
}

void GeoProtocol::forwardDataPacket(GeoRoutingPacket* pkt){
	
	auto t = findNextHop(pkt);
	int nextHop = std::get<0>(t);
	GeoRoutingPacket *dataPacket = std::get<1>(t);
	
	routing->sendToNextHop(dataPacket, nextHop);
	
	return;
}

void GeoProtocol::setTimer(int event, double timeDelay) {
	routing->setTimerEvent(event, timeDelay);
};

std::ostream & GeoProtocol::trace() {
	return (ostream &) routing->Trace();
}

void GeoProtocol::sendToNextHop(GeoPacket* dataPacket, int nextHop) {
	routing->sendToNextHop(dataPacket, nextHop);
};
		
NodeLocation_type GeoProtocol::getCurLocation() {
	return routing->getCurLocation();
};