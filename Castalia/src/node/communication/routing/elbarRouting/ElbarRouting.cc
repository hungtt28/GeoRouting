/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "ElbarRouting.h"

Define_Module(ElbarRouting);


void ElbarRouting::forwardDataPacket(GeoPacket* geoPacket)
{
	BHRoutingPacket *dataPacket = dynamic_cast <BHRoutingPacket*>(geoPacket->dup());
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	
	int nextHop = -1;
    switch (dataPacket->getRoutingMode()) {
		
        case BOUNDHOLE_GREEDY_ROUTING: {
			nextHop = findElbarNextHop(dataPacket);
			break;
		}
        case BOUNDHOLE_BOUNDHOLE_ROUTING: {
			nextHop = findBoundHoleRoutingNextHop(dataPacket);
			break;
		}
		case ELBAR_ADJUST_ROUTING: {
			nextHop = findAdjustRoutingNextHop(dataPacket);
			break;
		}
        default: break;
    }
	
	sendToNextHop(dataPacket, nextHop);
	
	return;
}

int ElbarRouting::findElbarNextHop(BHRoutingPacket* dataPacket) {
	
	int nextHop = -1;
	
	// decide to switch to adjust mode
	bool isStucked = false;
	NodeLocation_type desLocation = dataPacket->getDestinationLocation();
	for (int i = 0; i < holeCovers.size(); i++) {
		double pA = getAngle(curLocation, holeCovers[i].anchorList.pointA);
		double pC = getAngle(curLocation, holeCovers[i].anchorList.pointC);
		double pD = getAngle(curLocation, desLocation);
		double ApD = getAngle(pD, pA);
		double DpC = getAngle(pC, pD);
		double ApC = getAngle(pC, pA);
		if (ApD + DpC - ApC < ZERO) {
			double dPA = distance(curLocation, holeCovers[i].anchorList.pointA);
			double dPC = distance(curLocation, holeCovers[i].anchorList.pointC);
			double dPD = distance(curLocation, desLocation);
			if (dPD > dPA || dPD > dPC) {
				isStucked = true;
				dataPacket->setRoutingMode(ELBAR_ADJUST_ROUTING);
				double dAD = distance(holeCovers[i].anchorList.pointA, desLocation);
				double dCD = distance(holeCovers[i].anchorList.pointC, desLocation);
				if (dPA + dAD < dPC + dCD)
					dataPacket->setStartBoundHoleLocation(holeCovers[i].anchorList.pointA);
				else
					dataPacket->setStartBoundHoleLocation(holeCovers[i].anchorList.pointC);
				nextHop = findAdjustRoutingNextHop(dataPacket);
				break;
			}
		}
		// trace() << "[A] " << curId << " : " << ApD << " " << DpC << " " << ApC;
	}
	
	if (nextHop == -1)
		nextHop = findGreedyRoutingNextHop(dataPacket);
	
	return nextHop;
}

int ElbarRouting::findAdjustRoutingNextHop(BHRoutingPacket* dataPacket) {
	
	int nextHop = -1;
	double dist = -1;
	
	NodeLocation_type desLocation = dataPacket->getStartBoundHoleLocation();
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
		dataPacket->setRoutingMode(BOUNDHOLE_GREEDY_ROUTING);
		nextHop = findGreedyRoutingNextHop(dataPacket);
	}
	
	return nextHop;
}

void ElbarRouting::sendRefreshPacket(GeoPacket* geoPacket)
{
	BHPacket *bhPacket = dynamic_cast <BHPacket*>(geoPacket);
	
	// // in initiator construct A-polygon, otherwise broadcast hole info
	// if (bhPacket->getBForce() == false) {
		// // calculate A-polygon, 
		// holeApproximationByGridBase(bhPacket);
		// bhPacket->setBForce(true);
	// }
	
	// save polygon info
	int originalId = bhPacket->getOriginalId();
	int holeId = bhPacket->getHoleId();
	int sequenceNumber = bhPacket->getSequenceNumber();
	int iHole = -1;
	
	for (int i = 0; i < holeCovers.size(); i++) {
		if (holeCovers[i].originalId == originalId && holeCovers[i].holeId == holeId) {
			iHole = i;
			break;
		}
	}
	
	if (iHole == -1 || holeCovers[iHole].sequenceNumber != sequenceNumber) {
		// 
		AnchorList anchorList = holeCoveringParallelogram(bhPacket->getBoundHoleNodes());
		if (anchorList.isView) {
			if (iHole == -1) {
				holeCovers.push_back(HoleCoveringInfo(originalId, holeId, sequenceNumber, anchorList));
				boundHoles.push_back(BoundHoleInfo(originalId, holeId, bhPacket->getBoundHoleNodes()));
			}
			else {
				// update hole
				holeCovers[iHole].sequenceNumber = sequenceNumber;
				holeCovers[iHole].anchorList = anchorList;
				boundHoles[iHole].boundHoleNodes = bhPacket->getBoundHoleNodes();
			}
			// if hole view angle > alpha min then broadcast HCI message
			double pA = getAngle(curLocation, anchorList.pointA);
			double pC = getAngle(curLocation, anchorList.pointC);
			double viewAngle = getAngle(pC, pA);
			trace() << "[A] " << curId << " : " << originalId << " " << viewAngle << " " << anchorList.pointA.x << " " << anchorList.pointA.y;
			if (viewAngle > alpha_min) {
				// toMacLayer(bhPacket->dup(), BROADCAST_MAC_ADDRESS);
			}
		}
	}
	
	return;
}

AnchorList ElbarRouting::holeCoveringParallelogram(Nodes boundholeNodes) {
	
	AnchorList anchorList;
	
	// find Ai, Aj
	int i = 0, j = 0;
	double minAngle = getAngle(curLocation, boundholeNodes[0].nodeLocation);;
	double maxAngle = minAngle;
	double curAngle = minAngle;
	double dirAngle = minAngle;
	cout << curId << " " << boundholeNodes.size() << endl;
	cout << "fuck " << boundholeNodes[1].nodeId << endl;
	for (int k = 1; k < boundholeNodes.size(); k++) {
		cout << curId << " " << boundHoleNodes[k].nodeId << endl;
		// if (boundHoleNodes[k].nodeId == curId)
			// continue;
		double nextAngle = getAngle(curLocation, boundholeNodes[k].nodeLocation);
		double difAngle = getAngle(curAngle, nextAngle);
		dirAngle = difAngle < M_PI ? dirAngle + difAngle : dirAngle + difAngle - 2 * M_PI;
		if (maxAngle < dirAngle) {
			i = k;
			maxAngle = dirAngle;
		}
		if (minAngle > dirAngle) {
			j = k;
			minAngle = dirAngle;
		}
		curAngle = nextAngle;
	}
	trace() << "[A2] " << curId << " " << maxAngle << " " << minAngle;
	if (maxAngle - minAngle < alpha_max && maxAngle - minAngle > alpha_min) {
		// find V*, V**
		double hi = 0;
		double hj = 0;
		int vi = 0, vj = 0;
		for (int k = 0; k < boundholeNodes.size(); k++) {
			double height = distancePoint2Line(boundholeNodes[k].nodeLocation, boundholeNodes[i].nodeLocation, curLocation);
			if (height > hi) {
				vi = k;
				hi = height;
			}
			height = distancePoint2Line(boundholeNodes[k].nodeLocation, boundholeNodes[j].nodeLocation, curLocation);
			if (height > hj) {
				vj = k;
				hj = height;
			}
		}
		// calc A, C
		NodeLocation_type tempLocation;
		tempLocation.x = boundholeNodes[vj].nodeLocation.x + curLocation.x - boundholeNodes[j].nodeLocation.x;
		tempLocation.y = boundholeNodes[vj].nodeLocation.y + curLocation.y - boundholeNodes[j].nodeLocation.y;
		anchorList.pointA = intersectSections2(curLocation, boundholeNodes[i].nodeLocation, boundholeNodes[vj].nodeLocation, tempLocation);
		tempLocation.x = boundholeNodes[vi].nodeLocation.x + curLocation.x - boundholeNodes[i].nodeLocation.x;
		tempLocation.y = boundholeNodes[vi].nodeLocation.y + curLocation.y - boundholeNodes[i].nodeLocation.y;
		anchorList.pointC = intersectSections2(curLocation, boundholeNodes[j].nodeLocation, boundholeNodes[vi].nodeLocation, tempLocation);
		trace() << "[A1] " << curId << " : " << curLocation.x << " " << boundholeNodes[j].nodeLocation.x << " " << boundholeNodes[vi].nodeLocation.x << " " << tempLocation.x << " " << anchorList.pointC.x;
		trace() << "[A1] " << curId << " : " << curLocation.y << " " << boundholeNodes[j].nodeLocation.y << " " << boundholeNodes[vi].nodeLocation.y << " " << tempLocation.y << " " << anchorList.pointC.y;
		anchorList.isView = true;
	}
	else {
		// not handle !!!
	}
	
	// if (maxAngle - minAngle < 2 * M_PI)
		// anchorList.isView = true;
	
	return anchorList;
}

// void ElbarRouting::holeApproximationByGridBase(BHPacket* bhPacket) {
	
	// Nodes Apolygon;
	// Nodes boundholeNodes = bhPacket->getBoundHoleNodes();
	
	// // pick min, max coordinates
	// double max_x = 0, max_y = 0, min_x = 0, min_y = 0;
	// for (int k = 1; k < boundholeNodes.size() - 1; i++) {
		// if (boundholeNodes[k].nodeLocation.y < min_y)
			// min_y = boundholeNodes[k].nodeLocation.y;
		// if (boundholeNodes[k].nodeLocation.y > max_y)
			// max_y = boundholeNodes[k].nodeLocation.y;
		// if (boundholeNodes[k].nodeLocation.x < min_x)
			// min_x = boundholeNodes[k].nodeLocation.x;
		// if (boundholeNodes[k].nodeLocation.x > max_x)
			// max_x = boundholeNodes[k].nodeLocation.y;
	// }
	
	// int n = (max_x - min_x) / range + 1;
	// int m = (max_y - min_y) / range + 1;
	// char bmp = malloc(n * m);
	// memset(bmp, 0, n * m);
	// for (int k = 0; k < boundholeNodes.size(); k++) {
		// int i = (boundholeNodes[k].nodeLocation.x - min_x) / range;
		// int j = (max_y - boundholeNodes[k].nodeLocation.y) / range;
		// bmp[n * j + i] = 1;
	// }
	
	// int bmp2 = malloc(2 * m);
	// memset(bmp2, 0, 2 * m);
	// for (int j = 0; j < m; j++) {
		// for (int i = 0; i < n; i++) {
			// if (bmp[n * j + i] && left == 0)
				// bmp2[j] = i;		// left
			// if (bmp[n * j + i])
				// bmp2[m + j] = i;	// right
		// }
	// }
	
	// NodeLocation_type tNode;
	// tNode.x = min_x + bmp2[0] * range;
	// tNode.y = max_y;
	// Apolygon.push_back(Node(-1, tNode));
	// tNode.x = min_x + (bmp2[m] + 1) * range;
	// tNode.y = max_y;
	// Apolygon.push_back(Node(-1, tNode));
	// for (int j = 0; j < m - 1; j++) {
		// if (bmp2[j] != bmp2[j+1]) {
			// tNode.x = min_x + bmp2[j] * range;
			// tNode.y = max_y - (j + 1) * range;
			// Apolygon.insert(Apolygon.begin(), Node(-1, tNode));
			// tNode.x = min_x + bmp2[j+1] * range;
			// tNode.y = max_y - (j + 1) * range;
			// Apolygon.insert(Apolygon.begin(), Node(-1, tNode));
		// }
		// if (bmp2[m + j] != bmp2[m + j + 1]) {
			// tNode.x = min_x + (bmp2[j] + 1) * range;
			// tNode.y = max_y - (j + 1) * range;
			// Apolygon.push_back(Node(-1, tNode));
			// tNode.x = min_x + (bmp2[j+1] + 1) * range;
			// tNode.y = max_y - (j + 1) * range;
			// Apolygon.push_back(Node(-1, tNode));
		// }
	// }
	// tNode.x = min_x + bmp2[m-1] * range;
	// tNode.y = max_y - (m + 1) * range;
	// Apolygon.insert(Apolygon.begin(), Node(-1, tNode));
	// tNode.x = min_x + (bmp2[m + m-1] + 1) * range;
	// tNode.y = max_y - (m + 1) * range;
	// Apolygon.push_back(Node(-1, tNode));
	
	// bhPacket->getBoundHoleNodes().clear();
	// bhPacket->setBoundHoleNodes(Apolygon);
	// if (bmp) free(bmp);
	// if (bmp2) free(bmp2);
	
	// return;
// }



