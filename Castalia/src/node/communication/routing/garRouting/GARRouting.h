
/*
 * WSN GARgraphic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#ifndef _GARROUTING_H_
#define _GARROUTING_H_

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
#include "GARRoutingPacket_m.h"


using namespace std;


enum GARRoutingTimers {
    GAR_HELLO_MSG_REFRESH_TIMER = 0,
};

class GARRouting: public VirtualRouting {
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

    // GARRouting-related member variables
	bool isCoordinateSet = false; // to know whether the node's position has been set or not
    int totalSNnodes;
    int packetsPerNode;
    int seqHello;
	NodeLocation_type curLocation;
	NeighborTable *neighborTable;

 protected:

    void startup();
    void finishSpecific();
    void fromApplicationLayer(cPacket *, const char *);
    void fromMacLayer(cPacket *, int, double, double);
	void handleNetworkControlCommand(cMessage *);
    void timerFiredCallback(int);
    // void processBufferedPacket();

    void sendHelloMessage();
	void forwardDataPacket(GARRoutingPacket* dataPacket);
	void sendToNextHop(GeoPacket* dataPacket, int nextHop);

    int findGreedyRoutingNextHop(GARRoutingPacket* dataPacket);
    int findGARRoutingNextHop(GARRoutingPacket* dataPacket);
    int getNextNeighborCounterClockWiseByRollingBall(const int startNeighborAddress, double startNeighborAngle);
};

#endif				//GARROUTINGMODULE
