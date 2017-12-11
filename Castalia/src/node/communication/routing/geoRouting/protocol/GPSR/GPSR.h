/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _GPSR_H_
#define _GPSR_H_

#include "GeoProtocol.h"
#include "GPSRPacket_m.h"

using namespace std;

#define GPSR_RNG_PLANARIZATION 	string("RNG")
#define GPSR_GG_PLANARIZATION 	string("GG")

class GPSR: public GeoProtocol {
		
	public:
		string planarizationMode;
		
		void setProtocolMode(string protocolMode) {
			planarizationMode = protocolMode;
		}
		
	protected:
		int findGreedyRoutingNextHop(GPSRPacket* dataPacket);
		int findPerimeterRoutingNextHop(GPSRPacket* dataPacket);
		std::vector<int> getPlanarNeighbors();
		int getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle);
		
	public:
		GeoRoutingPacket* createGeoRoutingPacket();
		std::tuple<int, GeoRoutingPacket*> findNextHop(GeoRoutingPacket* pkt);
		
};

#endif