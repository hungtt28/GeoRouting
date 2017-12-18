/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "BoundHoleRouting.h"

Define_Module(BoundHoleRouting);

//================================================================
//    startup
//================================================================
void BoundHoleRouting::startup(){

	isCoordinateSet = false;
    
    helloInterval = (double)par("helloInterval") / 1000.0;
    activeRouteTimeout = (double)par("activeRouteTimeout") / 1000.0;
    packetsPerNode = par("packetsPerNode");
	seqHello = par("seqHello");
	
	neighborTable = new NeighborTable();
	
	// initialize
	range = 40;
	curId = atoi(SELF_NETWORK_ADDRESS);
	
	setTimer(BOUNDHOLE_UPDATE_EVENT, 3 * helloInterval);
	
	// set timer start bounddhole process
	setTimer(BOUNDHOLE_SUPPRESSED_START_EVENT, 5 * helloInterval);
	
	declareOutput("GPSR Packets received");
	declareOutput("GPSR Packets sent");
	declareOutput("GPSR Packets forwarded");

	// we will only send HELLO message if the node's coordinates are set
}

//================================================================
//    timerFiredCallback
//================================================================
void BoundHoleRouting::timerFiredCallback(int index){

	switch(index){
		case HELLO_MSG_REFRESH_TIMER :{
			sendHelloMessage();
			break;
		}
		
		case BOUNDHOLE_SUPPRESSED_START_EVENT: {
			suppressedStart();
			break;
		}
		
		case BOUNDHOLE_UPDATE_EVENT: {
			// get order neighbor counterclockwise
			orderNeighborCounterClockwise();
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
void BoundHoleRouting::handleNetworkControlCommand(cMessage *msg) {

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
//    fromApplicationLayer
//================================================================
void BoundHoleRouting::fromApplicationLayer(cPacket * pkt, const char *destination){  

	BHRoutingPacket *dataPacket = new BHRoutingPacket("BoundHole routing data packet", NETWORK_LAYER_PACKET);
	GeoApplicationPacket *appPacket = check_and_cast <GeoApplicationPacket*>(pkt);
	NodeLocation_type desLocation = appPacket->getDestinationLocation();

	encapsulatePacket(dataPacket, appPacket);
	dataPacket->setSequenceNumber(appPacket->getSequenceNumber());
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
void BoundHoleRouting::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi){
	
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
			
			BHRoutingPacket *routingPacket = dynamic_cast <BHRoutingPacket*>(pkt);
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
		
		// process control packet
		case GEO_CONTROL_PACKET: {
			GeoControlPacket *controlPacket = dynamic_cast <GeoControlPacket*>(pkt);
			processControlPacket(controlPacket);
			break;
		}
		
        default: return;
	}
}

//================================================================
//    finishSpecific
//================================================================
void BoundHoleRouting::finishSpecific() {

}

//================================================================
//    sendHelloMsg
//================================================================
void BoundHoleRouting::sendHelloMessage(){
	
    GeoBeaconPacket *helloMsg = new GeoBeaconPacket("Geo hello message packet", NETWORK_LAYER_PACKET);
    helloMsg->setSource(SELF_NETWORK_ADDRESS);
	helloMsg->setNodeLocation(curLocation);
    toMacLayer(helloMsg, BROADCAST_MAC_ADDRESS);
	
	seqHello++;
	setTimer(HELLO_MSG_REFRESH_TIMER, helloInterval);
	
	return;
}

void BoundHoleRouting::forwardDataPacket(BHRoutingPacket* pkt) {
	
	BHRoutingPacket *dataPacket = pkt->dup();
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
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
	
	sendToNextHop(dataPacket, nextHop);
	
	return;
}

void BoundHoleRouting::sendToNextHop(GeoPacket* dataPacket, int nextHop) {
	
	// send packet to nexthop
	string destination(dataPacket->getDestination());
	string source(dataPacket->getSource());
	if (nextHop != -1) {
		trace() << setw(10) << "SEND" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination << "currentHop " << setw(10) << SELF_NETWORK_ADDRESS << "nextHop " << setw(10) << nextHop;
		dataPacket->setSourceId(curId);
		toMacLayer(dataPacket, nextHop);
    }
	else {
		trace() << setw(10) << "DROP" << "PACKET #" << setw(10) << dataPacket->getSequenceNumber() << "FROM " << setw(10) << source << "TO " << setw(10) << destination;
		delete dataPacket;
    }
	
	return;
}


int BoundHoleRouting::findGreedyRoutingNextHop(BHRoutingPacket* dataPacket) {
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	int nextHop = -1;
	double dist = -1;
	double minDist = distance(curLocation, desLocation);
	
	// greedy
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
		dataPacket->setHoleId(-1);
		dataPacket->setOriginalId(-1);
		dataPacket->setStartIndex(-1);
		dataPacket->setCurIndex(-1);
		dataPacket->setDirection(true);
		nextHop = findBoundHoleRoutingNextHop(dataPacket);
	}
	
	return nextHop;
}

int BoundHoleRouting::findBoundHoleRoutingNextHop(BHRoutingPacket* dataPacket) {
	
	int nextHop = -1;
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	NodeLocation_type startBoundHoleLocation = dataPacket->getStartBoundHoleLocation();
	double curDistance = distance(curLocation, desLocation);
	double startBoundHoleDistance = distance(startBoundHoleLocation, desLocation);
	
	if (startBoundHoleDistance - curDistance > ZERO) {
		// back to greedy mode
		dataPacket->setRoutingMode(BOUNDHOLE_GREEDY_ROUTING);
		nextHop = findGreedyRoutingNextHop(dataPacket);
	}
	else {
		int holeId = dataPacket->getHoleId();
		if (holeId == -1 || (dataPacket->getCurIndex() == dataPacket->getStartIndex())) {
			holeId = findNextBoundHole(dataPacket);
		}
		trace() << "BoundHole " << curId << " " << holeId << " " << dataPacket->getOriginalId();
		// if no more boundhole, drop the packet
		if (holeId != -1) {
			// get nextHop in direction boundhole
			int direction = dataPacket->getDirection();
			int originalId = dataPacket->getOriginalId();
			for (int i = 0; i < boundHoles.size(); i++) {
				if (boundHoles[i].holeId == holeId && boundHoles[i].originalId == originalId) {
					trace() << "BoundHole " << curId << " " << holeId << " " << boundHoles[i].originalId;
					Nodes boundHoleNodes = boundHoles[i].boundHoleNodes;
					int curIndex = dataPacket->getCurIndex();
					if (boundHoleNodes[curIndex].nodeId == curId) {
						int nextIndex = direction ? curIndex + 1 : curIndex - 1;
						nextIndex = nextIndex < 1 ? boundHoleNodes.size() - 2 : nextIndex;
						nextIndex = nextIndex > boundHoleNodes.size() - 2 ? 1 : nextIndex;
						nextHop = boundHoleNodes[nextIndex].nodeId;
						dataPacket->setCurIndex(nextIndex);
					}
					break;
				}
			}
		}
	}
	
	return nextHop;
}

int BoundHoleRouting::findNextBoundHole(BHRoutingPacket* dataPacket) {
	
	int nextHoleId = -1;
	
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	double desAngle = getAngle(curLocation, desLocation);
	
	// boundhole greedy
	// get the closest to destination among u, v of all stuck angle
	double curDistance = distance(curLocation, desLocation);
	double minDistance = std::numeric_limits<double>::max();
	int holeId = dataPacket->getHoleId();
	int originalId = dataPacket->getOriginalId();
	for (int i = 0; i < boundHoles.size(); i++) {
		// a node have maximum 2 hole?
		if (boundHoles[i].holeId == holeId && boundHoles[i].originalId == originalId)
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
			nextHoleId = boundHoles[i].holeId;
			// 
			dataPacket->setHoleId(boundHoles[i].holeId);
			dataPacket->setOriginalId(boundHoles[i].originalId);
			dataPacket->setStartIndex(head);
			dataPacket->setCurIndex(head);
			dataPacket->setDirection(head <= tail);
			// dataPacket->setStartIngressId(boundHoleNodes[head - (tail - head)/fabs(tail - head)].nodeId);
		}
	}
	
	return nextHoleId;
}

// process control packet
void BoundHoleRouting::processControlPacket(GeoControlPacket *pkt) {
	
	BHPacket *bhPacket = dynamic_cast <BHPacket*>(pkt);
	
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
				bhPacket->setHoleId(holeCount++);
				bhPacket->setINode(1);	// index in boundhole nodes vector
				bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
				
				// boundHoles.push_back(BoundHoleInfo(curId, holeCount++, bhPacket->getBoundHoleNodes()));
				
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
					if (originalId > ingressEdgeList[iEdge].lowestId) {
						trace() << "drop " << originalId << " lowest " << ingressEdgeList[iEdge].lowestId;
						break;	// drop
					}
					else {
						ingressEdgeList[iEdge].lowestId = originalId;
					}
				}

				// send to nexthop
				int nextHop = getNeighborCounterClockwise(bhPacket);
				
				if (nextHop != -1) {
					bhPacket = dynamic_cast <BHPacket*>(pkt->dup());
					bhPacket->setSourceId(curId);
					sendToNextHop(bhPacket, nextHop);
					trace() << "[+] send " << originalId << " : " << curId << " -> " << nextHop;
				}
			}
			
			break;
		}
		
		case BOUNDHOLE_REFRESH_MODE: {
			
			if (bhPacket->getOriginalId() == curId)
				break;	// refresh done
			
			sendRefreshPacket(bhPacket);
			break;
		}
		
		default: break;
	}
	
	return;
}

// suppressed start
void BoundHoleRouting::suppressedStart() {
	
	// find stuck angle
	findStuckAngle();
	
	// send bounddhole
	for (auto &stuckAngle : stuckList) {
		// add new ingress edge u, send to v
		ingressEdgeList.push_back(IngressEdge(curId, stuckAngle.u.nodeId));
		
		BHPacket *bhPacket = new BHPacket("BoundHole control packet", NETWORK_LAYER_PACKET);
		bhPacket->setBoundHoleMode(BOUNDHOLE_SUPPRESSED_START_MODE);
		bhPacket->setOriginalId(curId);
		bhPacket->setSourceId(curId);
		bhPacket->getBoundHoleNodes().push_back(Node(stuckAngle.u.nodeId, stuckAngle.u.nodeLocation));
		bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
		sendToNextHop(bhPacket, stuckAngle.v.nodeId);
		trace() << "[*] " << stuckAngle.u.nodeId << " -> " << curId << " -> " << stuckAngle.v.nodeId;
	}
	
	return;
}

//
// Find StuckAngle by TENT rule
//
void BoundHoleRouting::findStuckAngle() {

	for (int i = 0; i < orderNeighbors.size() - 1; i++) {
		
		NodeAngle u = orderNeighbors[i];
		NodeAngle v = orderNeighbors[i+1];
		double upv = getAngle(u.nodeAngle, v.nodeAngle);
		// double upv = v.nodeAngle - u.nodeAngle;
		// if (upv < ZERO)
			// upv += 2 * M_PI;
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
				// not stuck
				continue;
			}
		}
		
		stuckList.push_back(StuckAngle(u, v));
	}
}

// order all 1-hop neighbor counterclockwise
// we create a circle list by set first order neighbor at last
void BoundHoleRouting::orderNeighborCounterClockwise() {
	
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
	
	// if (orderNeighbors.size()) {
		// trace() << "orderNeighbors node " << curId;
		// for (int i = 0; i < orderNeighbors.size() - 1; i++) {
			// trace() << "[*] " << orderNeighbors[i].nodeId << " " << orderNeighbors[i].nodeAngle;
		// }
	// }
	
	return;
}

// get neighbor s1 from direction tps0
int BoundHoleRouting::getNeighborCounterClockwise(BHPacket* bhPacket) {
	
	int nextHop = -1;
	int iNode = -1;
	
	// find ingress node in order neighbor
	int ingressId = bhPacket->getBoundHoleNodes().back().nodeId;
	if (orderNeighbors.size()) {
		for (int i = 0; i < orderNeighbors.size() - 1; i++) {
			if (orderNeighbors[i].nodeId == ingressId) {
				iNode = i;
				break;
			}
		}
	}
	
	// edge intersection
	bool hasIntersection = false;
	if (iNode != -1) {
		Nodes boundHoleNodes = bhPacket->getBoundHoleNodes();
		nextHop = orderNeighbors[iNode+1].nodeId;
		NodeLocation_type nextHopLocation = orderNeighbors[iNode+1].nodeLocation;
		if (nextHop == bhPacket->getOriginalId())
			return nextHop;
		for (int i = 0; i < boundHoleNodes.size() - 1; i++) {
			hasIntersection = intersectSections(boundHoleNodes[i].nodeLocation, boundHoleNodes[i+1].nodeLocation, curLocation, nextHopLocation);
			// hasIntersection = (nextHop == boundHoleNodes[i+1].nodeId && curId != boundHoleNodes[i].nodeId) ? true : hasIntersection;
			if (hasIntersection) {
				// TiTi+1 intersect TjTj+1 (i < j), type 1: Tj is not a neighbor of Ti, Ti+1, otherwise type 2
				// bool isNeighbor1 = false;
				// bool isNeighbor2 = false;
				// for (int j = 0; j < orderNeighbors.size() - 1; j++) {
					// if (orderNeighbors[j].nodeId == boundHoleNodes[i].nodeId)
						// isNeighbor1 = true;
					// if (orderNeighbors[j].nodeId == boundHoleNodes[i+1].nodeId)
						// isNeighbor2 = true;
				// }
				// if (isNeighbor1 && isNeighbor2) {
				double iAngle = getAngle(curLocation, boundHoleNodes[i].nodeLocation);
				double jAngle = getAngle(curLocation, boundHoleNodes[i+1].nodeLocation);
				if (getAngle(iAngle, jAngle) < M_PI) {
					// type2
					trace() << "[-] " << bhPacket->getOriginalId() << ": type2" << " " << nextHop << " " << boundHoleNodes[i].nodeId << " " << boundHoleNodes[i+1].nodeId;
					nextHop = boundHoleNodes[i].nodeId;
					bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
					bhPacket->getBoundHoleNodes().push_back(Node(boundHoleNodes[i+1].nodeId, boundHoleNodes[i+1].nodeLocation));
				}
				else {
					// type1, add new edge TiTj+1Tj then find nextHop
					trace() << "[-] " << bhPacket->getOriginalId() << ": type1" << " " << nextHop << " " << boundHoleNodes[i].nodeId << " " << boundHoleNodes[i+1].nodeId;
					bhPacket->getBoundHoleNodes().push_back(Node(boundHoleNodes[i].nodeId, boundHoleNodes[i].nodeLocation));
					bhPacket->getBoundHoleNodes().push_back(Node(nextHop, nextHopLocation));
					nextHop = getNeighborCounterClockwise(bhPacket);
					// bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
				}
				break;
			}
		}
	}
	if (nextHop != -1 && hasIntersection == false)
		bhPacket->getBoundHoleNodes().push_back(Node(curId, curLocation));
	trace() << "[-] " << bhPacket->getOriginalId() << ": " << ingressId << " " << curId << " " << nextHop << " " << hasIntersection;
	return nextHop;
}


// send refresh packet, broadcast hole information to all boundhole nodes
void BoundHoleRouting::sendRefreshPacket(BHPacket* pkt) {
	
	BHPacket* bhPacket = pkt->dup();
	
	int originalId = bhPacket->getOriginalId();
	int holeId = bhPacket->getHoleId();
	int iHole = -1;
	
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
	
	int nextHop = -1;
	int nextNode = bhPacket->getINode() + 1;
	nextHop = bhPacket->getBoundHoleNodes()[nextNode].nodeId;
	bhPacket->setINode(nextNode);
	bhPacket->setSourceId(curId);
	sendToNextHop(bhPacket, nextHop);
	return;
}