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

#ifndef _ELBARROUTING_H_
#define _ELBARROUTING_H_

#include "BoundHoleRouting.h"

using namespace std;

#define ELBAR_ADJUST_ROUTING 2

struct AnchorList {
	bool isView = false;
	NodeLocation_type pointA;
	NodeLocation_type pointC;
	
	AnchorList() {};
	AnchorList(NodeLocation_type pointA, NodeLocation_type pointC):
		pointA(pointA),
		pointC(pointC) {};
};

struct HoleCoveringInfo {
	int originalId;
	int holeId;
	int sequenceNumber;
	AnchorList anchorList;
	
	HoleCoveringInfo(int originalId, int holeId, int sequenceNumber, AnchorList acList): 
		originalId(originalId),
		holeId(holeId),
		sequenceNumber(sequenceNumber),
		anchorList(anchorList) {};
};

class ElbarRouting: public BoundHoleRouting {
protected:
	double alpha_min = M_PI / 3;
	double alpha_max = 2 * M_PI / 3;
	std::vector<HoleCoveringInfo> holeCovers;
	
protected:

	// override
	void forwardDataPacket(GeoPacket* geoPacket);
	
	void sendRefreshPacket(GeoPacket* geoPacket);
	AnchorList holeCoveringParallelogram(Nodes boundholeNodes);
	
	int findElbarNextHop(BHRoutingPacket* dataPacket);
	int findAdjustRoutingNextHop(BHRoutingPacket* dataPacket);
};

#endif				//ELBARROUTINGMODULE
