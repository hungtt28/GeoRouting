/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GPSR.h"
#include "GeoRouting.h"


GeoRoutingPacket* GPSR::createGeoRoutingPacket() {
	return new GPSRPacket("GPSR routing data packet", NETWORK_LAYER_PACKET);
}


std::tuple<int, GeoRoutingPacket*> GPSR::findNextHop(GeoRoutingPacket* pkt) {
	
	GPSRPacket *dataPacket = dynamic_cast <GPSRPacket*>(pkt->dup());
	
	int nextHop = -1;
    switch (dataPacket->getRoutingMode()) {
		
        case GPSR_GREEDY_ROUTING: {
			nextHop = findGreedyRoutingNextHop(dataPacket);
			break;
		}
        case GPSR_PERIMETER_ROUTING: {
			nextHop = findPerimeterRoutingNextHop(dataPacket);
			break;
		}
        default: break;
    }
	
	return std::make_tuple(nextHop, dataPacket);
}


int GPSR::findGreedyRoutingNextHop(GPSRPacket* dataPacket) {
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	NodeLocation_type curLocation = routing->getCurLocation();
	
	int nextHop = -1;
	double dist = -1;
	double minDist = distance(curLocation, desLocation);
	
	// greedy
	NeighborTable *neighborTable = routing->getNeighborTable();
	for (int i = 0; i < neighborTable->size(); i++) {
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		dist = distance(neighborRecord->getNodeLocation(), desLocation);
		if (dist - minDist < ZERO) {
			minDist = dist;
			nextHop = neighborRecord->getId();
		}
	}
	
	// if perimeter
	if (nextHop == -1) {
		int curId = atoi(routing->getCurAddress());
		dataPacket->setRoutingMode(GPSR_PERIMETER_ROUTING);
		dataPacket->setStartPerimeterLocation(curLocation);
		dataPacket->setFirstSenderAddress(routing->getCurAddress());
		dataPacket->setFirstReceiverAddress(to_string(-1).c_str());
		dataPacket->setSenderAddress(to_string(-1).c_str());
		nextHop = findPerimeterRoutingNextHop(dataPacket);
	}
	return nextHop;
}

int GPSR::findPerimeterRoutingNextHop(GPSRPacket* dataPacket) {
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	NodeLocation_type startPeriLocation = dataPacket->getStartPerimeterLocation();
	NodeLocation_type curLocation = routing->getCurLocation();
	int curId = atoi(routing->getCurAddress());

	double curDistance = distance(curLocation, desLocation);
	double minPeriDistance = distance(startPeriLocation, desLocation);
	
	int nextHop = -1;
	
	if (minPeriDistance - curDistance > ZERO) {
		NodeLocation_type zeroLocation;
		zeroLocation.x = 0;
		zeroLocation.y = 0;
		dataPacket->setRoutingMode(GPSR_GREEDY_ROUTING);
		dataPacket->setStartPerimeterLocation(zeroLocation);
		// dataPacket->setForwardPerimeterLocation();
		nextHop = findGreedyRoutingNextHop(dataPacket);
	}
	else {
		int indexRecord = -1;
		bool hasIntersection;
        int firstSender = atoi(dataPacket->getFirstSenderAddress());
        int firstReceiver = atoi(dataPacket->getFirstReceiverAddress());
		nextHop = atoi(dataPacket->getSenderAddress());
		NodeLocation_type nextHopLocation;
		
		NeighborTable *neighborTable = routing->getNeighborTable();
        do {
            if (nextHop == -1)
                nextHop = getNextPlanarNeighborCounterClockwise(nextHop, getAngle(curLocation, desLocation));
            else {
				indexRecord = neighborTable->getNeighborIndex(nextHop);
				if (indexRecord == -1) {
					nextHop = -1;
				}
				else {
					nextHopLocation = neighborTable->getRecord(indexRecord)->getNodeLocation();
					nextHop = getNextPlanarNeighborCounterClockwise(nextHop, getAngle(curLocation, nextHopLocation));
				}
			}
            if (nextHop == -1)
                break;
			
			indexRecord = neighborTable->getNeighborIndex(nextHop);
			if (indexRecord == -1)
				break;
			nextHopLocation = neighborTable->getRecord(indexRecord)->getNodeLocation();
			
            hasIntersection = intersectSections(startPeriLocation, desLocation, curLocation, nextHopLocation);
			
            if (hasIntersection) {
                dataPacket->setFirstSenderAddress(to_string(curId).c_str());
                dataPacket->setFirstReceiverAddress(to_string(-1).c_str());
            }
			
        } while (hasIntersection);
		
        if (firstSender == curId && firstReceiver == nextHop) {
            nextHop = -1;
        }
        else {
            if (string(dataPacket->getFirstReceiverAddress()).compare(to_string(-1)) == 0)
                dataPacket->setFirstReceiverAddress(to_string(nextHop).c_str());
        }
	}
	
	dataPacket->setSenderAddress(to_string(curId).c_str());
	return nextHop;
}


std::vector<int> GPSR::getPlanarNeighbors() {
	
    std::vector<int> planarNeighbors;
	
	NodeLocation_type curLocation = routing->getCurLocation();
	NeighborTable *neighborTable = routing->getNeighborTable();
	
	for (unsigned int i = 0; i < neighborTable->size(); i++) {
		NodeLocation_type neighborLocation = neighborTable->getRecord(i)->getNodeLocation();
		// dist = distance(neighborRecord->getNodeLocation(), desLocation);
		if (planarizationMode.compare(GPSR_RNG_PLANARIZATION) == 0) {
			double neighborDistance = distance(curLocation, neighborLocation);
			for (unsigned int j = 0; j < neighborTable->size(); j++) {
				if (i == j)
					continue;
				NodeLocation_type witnessLocation = neighborTable->getRecord(j)->getNodeLocation();
				if (neighborDistance > distance(curLocation, witnessLocation) && neighborDistance > distance(witnessLocation, neighborLocation))
					goto eliminate;
			}
		}
		else if (planarizationMode.compare(GPSR_GG_PLANARIZATION) == 0) {
			NodeLocation_type middleLocation;
			middleLocation.x = (curLocation.x + neighborLocation.x) / 2;
			middleLocation.y = (curLocation.y + neighborLocation.y) / 2;
			double radius = distance(curLocation, neighborLocation) / 2;
			for (unsigned int j = 0; j < neighborTable->size(); j++) {
				if (i == j)
					continue;
				NodeLocation_type witnessLocation = neighborTable->getRecord(j)->getNodeLocation();
				if (radius > distance(witnessLocation, middleLocation))
					goto eliminate;
			}
		}
        else
            throw cRuntimeError("Unknown planarization mode");
        planarNeighbors.push_back(neighborTable->getRecord(i)->getId());
      eliminate:;
    }
	return planarNeighbors;
}

int GPSR::getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle) {
	
    int nextHop = startNeighborAddress;
    double nextHopAngleDifference = 2 * M_PI;
	
    std::vector<int> planarNeighbors = getPlanarNeighbors();
	
	NodeLocation_type curLocation = routing->getCurLocation();
	NeighborTable *neighborTable = routing->getNeighborTable();
    for (auto & neighborAddress : planarNeighbors) {
		int indexRecord = neighborTable->getNeighborIndex(neighborAddress);
		if (indexRecord == -1)
			continue;
		NodeLocation_type neighborLocation = neighborTable->getRecord(indexRecord)->getNodeLocation();
        double neighborAngle = getAngle(curLocation, neighborLocation);
        double neighborAngleDifference = neighborAngle - startNeighborAngle;
        if (neighborAngleDifference < 1e-10)
            neighborAngleDifference += 2 * M_PI;
        if (neighborAngleDifference < nextHopAngleDifference) {
            nextHopAngleDifference = neighborAngleDifference;
            nextHop = neighborAddress;
        }
		
    }
    return nextHop;
}


