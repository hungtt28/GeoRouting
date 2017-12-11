/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _BOUNDHOLE_H_
#define _BOUNDHOLE_H_

#include "GeoProtocol.h"
#include "BoundHolePacket_m.h"
#include "BoundHoleRoutingPacket_m.h"
#include <limits>

using namespace std;

enum BoundHoleEvent {
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

class BoundHole: public GeoProtocol {
		
	protected:
		double range;
		int curId;
		double helloInterval;
		std::vector<NodeAngle> orderNeighbors;
		std::vector<StuckAngle> stuckList;
		std::vector<IngressEdge> ingressEdgeList;
		Nodes boundHoleNodes;
		std::vector<BoundHoleInfo> boundHoles;
		int holeCount = 0;
		
	public:
		string planarizationMode;
		
		void setProtocolMode(string protocolMode) {
			planarizationMode = protocolMode;
		}
	
		void initialize();
		GeoRoutingPacket* createGeoRoutingPacket();
		std::tuple<int, GeoRoutingPacket*> findNextHop(GeoRoutingPacket* pkt);
		void processControlPacket(GeoControlPacket *pkt);
		void processTimerCallback(int index);
		
		int findGreedyRoutingNextHop(BoundHoleRoutingPacket* dataPacket);
		int findBoundHoleRoutingNextHop(BoundHoleRoutingPacket* dataPacket);
		int findNextBoundHole(BoundHoleRoutingPacket* dataPacket, int curHoleId);
		
		void update();
		
		// user define
		void suppressedStart();
		void findStuckAngle();
		void orderNeighborCounterClockwise();
		int getNeighborCounterClockwise(int ingressId, Node t, Node p);
		std::vector<int> getPlanarNeighbors();
		int getNextPlanarNeighborCounterClockwise(const int startNeighborAddress, double startNeighborAngle);
		void sendRefreshPacket(BoundHolePacket* pkt);
};

#endif