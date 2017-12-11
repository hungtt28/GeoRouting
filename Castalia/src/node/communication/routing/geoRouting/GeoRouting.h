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

#ifndef _GEOROUTING_H_
#define _GEOROUTING_H_

#include <map>
#include <tuple>
#include "VirtualRouting.h"
#include "GeoApplicationPacket_m.h"
#include "GeoRoutingControl_m.h"
#include "GeoPacket_m.h"
#include "GeoBeaconPacket_m.h"
#include "GeoRoutingPacket_m.h"
#include "GeoControlPacket_m.h"
#include "GeoProtocolHelper.h"


using namespace std;


enum GeoRoutingTimers {
    GEO_HELLO_MSG_REFRESH_TIMER = 0,
	GEO_TIMER = 1,
};

class GeoRouting: public VirtualRouting {
 private:
    // Parameters
    double netSetupTimeout;
    bool collectTraceInfo;
    int currentSequenceNumber;
    double helloInterval;
    double activeRouteTimeout; //in s

    // GeoRouting-related member variables
	bool isCoordinateSet = false; // to know whether the node's position has been set or not
    int totalSNnodes;
    int packetsPerNode;
    int seqHello;
	NodeLocation_type nodeLocation;
	NeighborTable *neighborTable;
	GeoProtocol *geoProtocol;

public:
	NodeLocation_type& getCurLocation() {
		return nodeLocation;
	};
	
	NeighborTable* getNeighborTable() {
		return neighborTable;
	};
	
	const char* getCurAddress() {
		return SELF_NETWORK_ADDRESS;
	};
	
	double getHelloInterval() {
		return helloInterval;
	};
	
	void setTimerEvent(int event, double timeDelay) {
		setTimer(event, timeDelay);
		return;
	}
	
	std::ostream & Trace() {
		return (ostream &) trace();
	}
	
	void sendToNextHop(GeoPacket* dataPacket, int nextHop);
	
 protected:

    void startup();
    void finishSpecific();
    void fromApplicationLayer(cPacket *, const char *);
    void fromMacLayer(cPacket *, int, double, double);
	void handleNetworkControlCommand(cMessage *);
    void sendTopologySetupPacket();
    void timerFiredCallback(int);
    void processBufferedPacket();

    void sendHelloMessage();

};

#endif				//GEOROUTINGMODULE
