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

#ifndef _GREEDYROUTING_H_
#define _GREEDYROUTING_H_

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
#include "GreedyRoutingPacket_m.h"


using namespace std;


enum GreedyRoutingTimers {
    GREEDY_HELLO_MSG_REFRESH_TIMER = 0,
};

class GreedyRouting: public VirtualRouting {
 private:
    // Parameters
    double netSetupTimeout;
    bool collectTraceInfo;
    int currentSequenceNumber;
    double helloInterval;
    double activeRouteTimeout; //in s

    // GreedyRouting-related member variables
	bool isCoordinateSet = false; // to know whether the node's position has been set or not
    int totalSNnodes;
    int packetsPerNode;
    int seqHello;
	NodeLocation_type nodeLocation;
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
	void forwardDataPacket(GreedyRoutingPacket* dataPacket);
	void sendToNextHop(GeoPacket* dataPacket, int nextHop);

};

#endif				//GREEDYROUTINGMODULE
