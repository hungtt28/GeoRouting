/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "BoundHole.h"
#include "GeoRouting.h"

void BoundHole::initialize() {
	
	range = 40;
	curId = atoi(routing->getCurAddress());
	helloInterval = routing->getHelloInterval();
	
	setTimer(BOUNDHOLE_UPDATE_EVENT, 3 * helloInterval);
	
	// set timer start bounddhole process
	setTimer(BOUNDHOLE_SUPPRESSED_START_EVENT, 5 * helloInterval);
	
	return;
};

void BoundHole::processTimerCallback(int event) {
	
	switch(event) {
		case BOUNDHOLE_SUPPRESSED_START_EVENT: {
			suppressedStart();
			break;
		}
		
		case BOUNDHOLE_UPDATE_EVENT: {
			update();
			break;
		}
		
		default: break;
	}
	
	return;
}

void BoundHole::update() {
	
	// get order neighbor counterclockwise
	orderNeighborCounterClockwise();
	
	return;
}

GeoRoutingPacket* BoundHole::createGeoRoutingPacket() {
	return new BoundHoleRoutingPacket("BoundHole routing data packet", NETWORK_LAYER_PACKET);
}

std::tuple<int, GeoRoutingPacket*> BoundHole::findNextHop(GeoRoutingPacket* pkt) {
	
	BoundHoleRoutingPacket *dataPacket = dynamic_cast <BoundHoleRoutingPacket*>(pkt->dup());
	
	int nextHop = -1;
    switch (dataPacket->getRoutingMode()) {
		
        case BOUNDHOLE_GREEDY_ROUTING: {
			nextHop = findGreedyRoutingNextHop(dataPacket);
			break;
		}
        case BOUNDHOLE_BOUNDHOLE_ROUTING: {
			nextHop = findBoundHoleRoutingNextHop(dataPacket);
			break;
		}
        default: break;
    }
	
	return std::make_tuple(nextHop, dataPacket);
}



int BoundHole::findGreedyRoutingNextHop(BoundHoleRoutingPacket* dataPacket) {
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	NodeLocation_type curLocation = getCurLocation();
	
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
	
	if (nextHop == -1) {
		// set boundhole info
		dataPacket->setRoutingMode(BOUNDHOLE_BOUNDHOLE_ROUTING);
		dataPacket->getStartBoundHoleLocation().x = curLocation.x;
		dataPacket->getStartBoundHoleLocation().y = curLocation.y;
		dataPacket->setStartBoundHoleId(curId);
		dataPacket->setStartIngressId(-1);
		dataPacket->setHoleId(-1);
		nextHop = findBoundHoleRoutingNextHop(dataPacket);
	}
	
	return nextHop;
}

int BoundHole::findBoundHoleRoutingNextHop(BoundHoleRoutingPacket* dataPacket) {
	
	int nextHop = -1;
	
	NodeLocation_type curLocation = getCurLocation();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	NodeLocation_type startBoundHoleLocation = dataPacket->getStartBoundHoleLocation();
	double curDistance = distance(curLocation, desLocation);
	double startBoundHoleDistance = distance(startBoundHoleLocation, desLocation);
	int holeId = dataPacket->getHoleId();
	int startBoundHoleId = dataPacket->getStartBoundHoleId();
	int startIngressId = dataPacket->getStartIngressId();
	
	if (startBoundHoleDistance - curDistance > ZERO) {
		// back to greedy mode
		dataPacket->setRoutingMode(BOUNDHOLE_GREEDY_ROUTING);
		nextHop = findGreedyRoutingNextHop(dataPacket);
	}
	else {
		if (holeId == -1 || (startBoundHoleId == curId && startIngressId == dataPacket->getSourceId())) {
			holeId = findNextBoundHole(dataPacket, holeId);
		}
		
		// if no more boundhole, drop the packet
		if (holeId != -1) {
			// get nextHop in direction ingressId, curId
			int ingressId = dataPacket->getSourceId();
			for (int i = 0; i < boundHoles.size(); i++) {
				if (boundHoles[i].holeId == holeId) {
					Nodes boundHoleNodes = boundHoles[i].boundHoleNodes;
					for (int j = 1; j < boundHoleNodes.size() - 1; j++) {
						if (boundHoleNodes[j].nodeId == curId) {
							if (boundHoleNodes[j - 1].nodeId == ingressId) {
								nextHop = boundHoleNodes[j + 1].nodeId;
								break;
							}
							if (boundHoleNodes[j + 1].nodeId == ingressId) {
								nextHop = boundHoleNodes[j - 1].nodeId;
								break;
							}
						}
					}
					break;
				}
			}
			cout << ingressId << " " << curId << " " << nextHop << endl;
		}
	}
	
	return nextHop;
}

int BoundHole::findNextBoundHole(BoundHoleRoutingPacket* dataPacket, int curHoleId) {
	
	int nextHoleId = -1;
	
	NodeLocation_type curLocation = getCurLocation();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	double desAngle = getAngle(curLocation, desLocation);
	
	// boundhole greedy
	// get the closest to destination among u, v of all stuck angle
	double curDistance = distance(curLocation, desLocation);
	double minDistance = std::numeric_limits<double>::max();
	for (int i = 0; i < boundHoles.size(); i++) {
		// a node have maximum 2 hole?
		if (boundHoles[i].holeId == curHoleId)
			continue;
		double boundDistance = std::numeric_limits<double>::max();
		Nodes boundHoleNodes = boundHoles[i].boundHoleNodes;
		std::vector<int> nodeIndexes;	// current node index
		std::vector<int> candidates;	// destination closest node index
		for (int j = 0; j < boundHoleNodes.size(); j++) {
			if (boundHoleNodes[j].nodeId == curId) {
				nodeIndexes.push_back(j);
				continue;
			}
			double nodeDistance = distance(boundHoleNodes[j].nodeLocation, desLocation);
			if (boundDistance - nodeDistance > ZERO) {
				candidates.clear();
				candidates.push_back(j);
				boundDistance = nodeDistance;
			}
			if (fabs(boundDistance - nodeDistance) < ZERO)
				candidates.push_back(j);
		}
		if (minDistance - boundDistance > ZERO) {
			// choose the best candidate
			int minHop = std::numeric_limits<int>::max();
			int head = -1;
			int tail = -1;
			for (auto h : nodeIndexes) {
				for (auto t : candidates) {
					int numHop = (fabs(t - h) <= boundHoleNodes.size() / 2) ? fabs(t - h) : boundHoleNodes.size() - fabs(t - h);
					if (numHop < minHop) {
						minHop = numHop;
						head = h; tail = t;
					}
				}
			}
			
			// nextHoleId = boundHoleNodes[head + (tail - head)/fabs(tail - head)].nodeId;
			nextHoleId = i;
			// update ingressId
			dataPacket->setHoleId(nextHoleId);
			dataPacket->setStartIngressId(boundHoleNodes[head - (tail - head)/fabs(tail - head)].nodeId);
		}
	}
	
	return nextHoleId;
}

// process control packet
void BoundHole::processControlPacket(GeoControlPacket *pkt) {
	
	BoundHolePacket *bhPacket = dynamic_cast <BoundHolePacket*>(pkt);
	NodeLocation_type curLocation = getCurLocation();
	
	switch(bhPacket->getBoundHoleMode()) {
		
		case BOUNDHOLE_SUPPRESSED_START_MODE: {
			/*
			note: we had added first ingress edge of stuck node (ingress node u send to v)
			receive bounddhole packet
			if (packet orginalId == nodeId)
				to refresh mode
			if (packet via exist ingress edge)
				if (orginalId not smaller than lowestId of ingress edge && not enforce)
					drop
			else add new ingress edge
			find nexthop counterclockwise
			send to nexthop
			*/
			
			int originalId = bhPacket->getOriginalId();
			if (originalId == curId) {
				
				bhPacket->setBoundHoleMode(BOUNDHOLE_REFRESH_MODE);
				bhPacket->setHoleId(holeCount);
				bhPacket->setINode(1);	// index in boundhole nodes vector
				bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
				
				boundHoles.push_back(BoundHoleInfo(curId, holeCount++, bhPacket->getBoundHoleNodes()));
				
				trace() << "BoundHole done";
				Nodes boundHoleNodes = bhPacket->getBoundHoleNodes();
				for (int i = 0; i < boundHoleNodes.size(); i++) {
					trace() << "[+] " << curId << " : " << boundHoleNodes[i].nodeId;
				}
				
				sendRefreshPacket(bhPacket);
				// delete bhPacket;
			}
			else {
				int sourceId = bhPacket->getSourceId();
				int iEdge = -1;
				for (int i = 0; i < ingressEdgeList.size(); i++) {
					if (sourceId == ingressEdgeList[i].ingressId) {
						iEdge = i;
						break;
					}
				}
				if (iEdge == -1) {
					// add new ingress edge
					ingressEdgeList.push_back(IngressEdge(originalId, sourceId));
					iEdge = ingressEdgeList.size() - 1;
				}
				if (bhPacket->getBForce() == false) {
					if (originalId > ingressEdgeList[iEdge].lowestId)
						break;	// drop
					else {
						ingressEdgeList[iEdge].lowestId = originalId;
					}
				}

				// send to nexthop
				Node t = bhPacket->getBoundHoleNodes().end()[-2];
				Node p = bhPacket->getBoundHoleNodes().end()[-1];
				int nextHop = getNeighborCounterClockwise(sourceId, t, p);
				
				if (nextHop != -1) {
					bhPacket = dynamic_cast <BoundHolePacket*>(pkt->dup());
					bhPacket->setSourceId(curId);
					bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
					sendToNextHop(bhPacket, nextHop);
				}
				trace() << "[+] send " << originalId << " : " << curId << " -> " << nextHop;
			}
			
			break;
		}
		
		case BOUNDHOLE_REFRESH_MODE: {
			
			int originalId = bhPacket->getOriginalId();
			int holeId = bhPacket->getHoleId();
			int iHole = -1;
			
			if (originalId == curId)
				break;	// refresh done
			
			for (int i = 0; i < boundHoles.size(); i++) {
				if (boundHoles[i].originalId == originalId && boundHoles[i].holeId == holeId) {
					iHole = i;
					break;
				}
			}
			if (iHole == -1)
				boundHoles.push_back(BoundHoleInfo(originalId, holeId, bhPacket->getBoundHoleNodes()));
			else
				boundHoles[iHole].boundHoleNodes = bhPacket->getBoundHoleNodes();
			
			sendRefreshPacket(bhPacket);
			break;
		}
		
		default: break;
	}
	
	return;
}

// suppressed start
void BoundHole::suppressedStart() {
	
	NodeLocation_type curLocation = getCurLocation();
	
	// find stuck angle
	findStuckAngle();
	
	// send bounddhole
	for (auto &stuckAngle : stuckList) {
		// add new ingress edge u, send to v
		ingressEdgeList.push_back(IngressEdge(curId, stuckAngle.u.nodeId));
		
		BoundHolePacket *bhPacket = new BoundHolePacket("BoundHole control packet", NETWORK_LAYER_PACKET);
		bhPacket->setBoundHoleMode(BOUNDHOLE_SUPPRESSED_START_MODE);
		bhPacket->setOriginalId(curId);
		bhPacket->setSourceId(curId);
		bhPacket->getBoundHoleNodes().push_back(Node(stuckAngle.u.nodeId, stuckAngle.u.nodeLocation));
		bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
		sendToNextHop(bhPacket, stuckAngle.v.nodeId);
		trace() << "[*] send " << curId << " -> " << stuckAngle.v.nodeId;
	}
	
	return;
}

//
// Find StuckAngle by TENT rule
//
void BoundHole::findStuckAngle() {
	
	NodeLocation_type curLocation = getCurLocation();

	for (int i = 0; i < orderNeighbors.size() - 1; i++) {
		
		NodeAngle u = orderNeighbors[i];
		NodeAngle v = orderNeighbors[i+1];
		double upv = getAngle(u.nodeAngle, v.nodeAngle);
		// double upv = v.nodeAngle - u.nodeAngle;
		// if (upv < ZERO)
			// upv += 2 * M_PI;
		trace() << "[!] " << curId << " | " << u.nodeId << " " << v.nodeId << " " << upv;
		if ((upv - 2 * M_PI / 3) < ZERO && u.nodeId != v.nodeId) {
			// not stuck
			continue;
		}
		
		if (upv - M_PI < ZERO) {
			NodeLocation_type OLocation = getCircumscribedcircleCenter(curLocation, u.nodeLocation, v.nodeLocation);
			
			double OAngle = getAngle(curLocation, OLocation);
			double upO = getAngle(u.nodeAngle, OAngle);
			double Opv = getAngle(OAngle, v.nodeAngle);
			
			if ((distance(curLocation, OLocation) - range) <= ZERO || (upO + Opv - upv) > ZERO) {
				trace() << "[!!] " << distance(curLocation, OLocation) << " " << upO << " " << Opv;
				// not stuck
				continue;
			}
			trace() << "[-] " << distance(curLocation, OLocation) << " " << curLocation.x << " " << curLocation.y << " " << u.nodeLocation.x << " " << u.nodeLocation.y << " " << v.nodeLocation.x << " " << v.nodeLocation.y << " " << OLocation.x << " " << OLocation.y;
		}
		trace() << "[-] " << curId << ": " << u.nodeId << " : " << v.nodeId << " : " << u.nodeAngle << " : " << v.nodeAngle << " : " << upv;
		stuckList.push_back(StuckAngle(u, v));
	}
}

// order all 1-hop neighbor counterclockwise
// we create a circle list by set first order neighbor at last
void BoundHole::orderNeighborCounterClockwise() {
	
	NodeLocation_type curLocation = getCurLocation();
	NeighborTable *neighborTable = routing->getNeighborTable();
	for (int i = 0; i < neighborTable->size(); i++) {
		
		NeighborRecord *neighborRecord = neighborTable->getRecord(i);
		double neighborAngle = getAngle(curLocation, neighborRecord->getNodeLocation());
		
		int orderNumber = -1;
		
		for (unsigned int j = 0; j < orderNeighbors.size(); j++) {
			if (neighborAngle < orderNeighbors[j].nodeAngle) {
				orderNumber = j;
				break;
			}
		}
		
		// insert neighbor to order list
		NodeAngle nodeAngle = NodeAngle(neighborRecord->getId(), neighborRecord->getNodeLocation(), neighborAngle);
		if (orderNumber == -1)
			orderNeighbors.push_back(nodeAngle);
		else
			orderNeighbors.insert(orderNeighbors.begin() + orderNumber, nodeAngle);
		
	}
	
	// set first neighbor to last to create cirle list
	if (orderNeighbors.size() > 0)
		orderNeighbors.push_back(NodeAngle(orderNeighbors[0].nodeId, orderNeighbors[0].nodeLocation, orderNeighbors[0].nodeAngle));
	
	return;
}

// get neighbor s1 from direction tps0
int BoundHole::getNeighborCounterClockwise(int ingressId, Node t, Node p) {
	
	int nextHop = -1;
	int iNode = -1;
	
	// find ingress node in order neighbor
	if (orderNeighbors.size()) {
		for (int i = 0; i < orderNeighbors.size() - 1; i++) {
			if (orderNeighbors[i].nodeId == ingressId) {
				iNode = i;
				break;
			}
		}
	}
	
	// tp, s0s1 do not intersect
	bool hasIntersection;
	NodeLocation_type curLocation = getCurLocation();
	do {
		iNode++;
		if (iNode == orderNeighbors.size())
			break;
		nextHop = orderNeighbors[iNode].nodeId;
		NodeLocation_type nextHopLocation = orderNeighbors[iNode].nodeLocation;
		hasIntersection = intersectSections(t.nodeLocation, p.nodeLocation, curLocation, nextHopLocation);
		trace() << "[++] " << curId << " " << nextHop << " " << t.nodeId << " " << p.nodeId << " " << hasIntersection;
	} while (hasIntersection);
	trace() << "*** " << curId << " " << orderNeighbors.size();
	if (nextHop == -1 && orderNeighbors.size()) {
		NeighborTable *neighborTable = routing->getNeighborTable();
		trace() << "[*] " << curId << " " << ingressId << " " << orderNeighbors.size() - 1 << " " << neighborTable->size();
		for (int i = 0; i < orderNeighbors.size() - 1; i++) {
			trace() << "[*] " << orderNeighbors[i].nodeId;
		}
	}
	
	return nextHop;
}


// send refresh packet, broadcast hole information to all boundhole nodes
void BoundHole::sendRefreshPacket(BoundHolePacket* pkt) {
	
	BoundHolePacket* bhPacket = pkt->dup();
	
	// send to downstream node in boundhole
	// int nextHop = -1;
	// for (int j = 0; j < bhPacket->getBoundHoleNodes().size(); j++) {
		// if (bhPacket->getBoundHoleNodes()[j].nodeId == curId) {
			// nextHop = bhPacket->getBoundHoleNodes()[j+1].nodeId;
			// break;
		// }
	// }
	// int nextHop = getNeighborCounterClockwise(bhPacket->getSourceId());
	int nextHop = -1;
	int nextNode = bhPacket->getINode() + 1;
	nextHop = bhPacket->getBoundHoleNodes()[nextNode].nodeId;
	bhPacket->setINode(nextNode);
	bhPacket->setSourceId(curId);
	sendToNextHop(bhPacket, nextHop);
	return;
}