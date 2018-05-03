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
 * WSN Greedygraphic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#ifndef _BOUNDHOLEROUTING_H_
#define _BOUNDHOLEROUTING_H_

#include <map>
#include <tuple>
#include "VirtualRouting.h"
#include "NeighborTable.h"
#include "GeoHelper.h"
#include "VirtualMobilityManager.h"
#include "GeoApplicationPacket_m.h"
#include "GeoRoutingControl_m.h"
#include "GeoPacket_m.h"
#include "GeoBeaconPacket_m.h"
#include "GeoControlPacket_m.h"

#include "BHPacket_m.h"
#include "BHRoutingPacket_m.h"
#include <limits>

using namespace std;


enum BoundHoleRoutingTimers {
    HELLO_MSG_REFRESH_TIMER = 0,
    BOUNDHOLE_SUPPRESSED_START_EVENT = 1,
	BOUNDHOLE_UPDATE_EVENT = 2,
};


struct NodeAngle {
	int nodeId;
	NodeLocation_type nodeLocation;
	double nodeAngle;
	
	NodeAngle(int id, NodeLocation_type nodeLocation, double angle): nodeId(id), nodeLocation(nodeLocation), nodeAngle(angle) {};
};

struct StuckAngle {
	NodeAngle u;
	NodeAngle v;
	
	StuckAngle(NodeAngle u, NodeAngle v): u(u), v(v) {};
};

struct IngressEdge {
	int lowestId;
	int ingressId;
	
	IngressEdge(int lowestId, int ingressId): lowestId(lowestId), ingressId(ingressId) {};
};

struct BoundHoleInfo {
	int originalId;
	int holeId;
	Nodes boundHoleNodes;
	
	BoundHoleInfo(int originalId, int holeId, Nodes boundHoleNodes): 
		originalId(originalId),
		holeId(holeId),
		boundHoleNodes(boundHoleNodes) {};
};


class BoundHoleRouting: public VirtualRouting {
protected:
    // Parameters
    double netSetupTimeout;
    bool collectTraceInfo;
    int currentSequenceNumber;
    double helloInterval;
    double activeRouteTimeout; //in s

    // BoundHoleRouting-related member variables
	bool isCoordinateSet = false; // to know whether the node's position has been set or not
    int totalSNnodes;
    int packetsPerNode;
    int seqHello;
	NodeLocation_type curLocation;
	NeighborTable *neighborTable;
	
	// user define
	double range;
	int curId;
	std::vector<NodeAngle> orderNeighbors;
	std::vector<StuckAngle> stuckList;
	std::vector<IngressEdge> ingressEdgeList;
	Nodes boundHoleNodes;
	std::vector<BoundHoleInfo> boundHoles;
	int holeCount = 0;
	int seqNumber = 0;
	
 protected:

    void startup();
    void finishSpecific();
    void fromApplicationLayer(cPacket *, const char *);
    void fromMacLayer(cPacket *, int, double, double);
	void handleNetworkControlCommand(cMessage *);
    void timerFiredCallback(int);
    // void processBufferedPacket();

    void sendHelloMessage();
	virtual void forwardDataPacket(GeoPacket* dataPacket);
	void sendToNextHop(GeoPacket* dataPacket, int nextHop);
	void processControlPacket(GeoControlPacket *pkt);
	
	// user define
	virtual int findGreedyRoutingNextHop(BHRoutingPacket* dataPacket);
	virtual int findBoundHoleRoutingNextHop(BHRoutingPacket* dataPacket);
	int findNextBoundHole(BHRoutingPacket* dataPacket);
	void suppressedStart();
	void findStuckAngle();
	void orderNeighborCounterClockwise();
	int getNeighborCounterClockwise(BHPacket* bhPacket);
	std::vector<int> getPlanarNeighbors();
	int getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle);
	virtual void sendRefreshPacket(GeoPacket* pkt);

};

#endif				//BOUNDHOLEROUTINGMODULE
