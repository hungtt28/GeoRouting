/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _NEIGHBORRECORD_H_
#define _NEIGHBORRECORD_H_

#include "VirtualMobilityManager.h"

class NeighborRecord {
	private:
		int id;
		NodeLocation_type nodeLocation;
		double ts;
		int timesRx;
		
	public:
		NeighborRecord(int id, NodeLocation_type nodeLocation): id(id), nodeLocation(nodeLocation) {};
		
		virtual int getId() {
			return id;
		};
		
		virtual NodeLocation_type getNodeLocation() {
			return nodeLocation;
		};
};

#endif