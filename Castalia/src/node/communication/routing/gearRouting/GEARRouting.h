
/*
 * WSN GEARgraphic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#ifndef _GEARROUTING_H_
#define _GEARROUTING_H_

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
#include "GEARRoutingPacket_m.h"
#include "GEARHelloPacket_m.h"


using namespace std;


enum GEARRoutingTimers {
    GEAR_HELLO_MSG_REFRESH_TIMER = 0,
};

class GEARRouting: public VirtualRouting {
 private:
    // Parameters
    double netSetupTimeout;
    bool collectTraceInfo;
    int currentSequenceNumber;
    double helloInterval;
    double activeRouteTimeout; //in s

	// user define
	double range;
	int curId;

    // GEARRouting-related member variables
	bool isCoordinateSet = false; // to know whether the node's position has been set or not
    int totalSNnodes;
    int packetsPerNode;
    int seqHello;
	NodeLocation_type curLocation;
	NeighborTable *neighborTable;
	
    // gear
    double learnedCost;
    double alpha;
    double consumedEnergy;

 protected:

    void startup();
    void finishSpecific();
    void fromApplicationLayer(cPacket *, const char *);
    void fromMacLayer(cPacket *, int, double, double);
	void handleNetworkControlCommand(cMessage *);
    void timerFiredCallback(int);
    // void processBufferedPacket();

    void sendHelloMessage();
	void forwardDataPacket(GEARRoutingPacket* dataPacket);
	void sendToNextHop(GeoPacket* dataPacket, int nextHop);

    int findGearRoutingNextHop(GEARRoutingPacket* dataPacket);
    int findLowestLearnedCost(NodeLocation_type desLocation, double minCost);
};

#endif				//GEARROUTINGMODULE
