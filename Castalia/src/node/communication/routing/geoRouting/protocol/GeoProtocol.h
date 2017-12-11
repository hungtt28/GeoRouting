/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _GEOPROTOCOL_H_
#define _GEOPROTOCOL_H_

#include "NeighborTable.h"
#include "GeoHelper.h"
#include "VirtualMobilityManager.h"
#include "GeoRoutingPacket_m.h"
#include "GeoControlPacket_m.h"
#include <tuple>

using namespace std;

class GeoRouting;

class GeoProtocol {
	protected:
		GeoRouting *routing;
		
	public:
		virtual void setGeoRouting(GeoRouting *geoRouting) {
			routing = geoRouting;
		};
		
		virtual void initialize() {};
		virtual std::tuple<int, GeoRoutingPacket*> findNextHop(GeoRoutingPacket* pkt);
		virtual GeoRoutingPacket* createGeoRoutingPacket();
		virtual void setProtocolMode(string protocolMode) {};
		virtual void forwardDataPacket(GeoRoutingPacket* pkt);
		virtual void processControlPacket(GeoControlPacket *pkt) {};
		virtual void processTimerCallback(int index) {};
		virtual void setTimer(int event, double timeDelay);
		virtual std::ostream & trace();
		virtual void sendToNextHop(GeoPacket* dataPacket, int nextHop);
		NodeLocation_type getCurLocation();
		
};

#endif