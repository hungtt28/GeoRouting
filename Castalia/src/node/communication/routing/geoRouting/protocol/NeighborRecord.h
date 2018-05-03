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
		double learnedCost;
		
	public:
		NeighborRecord(int id, NodeLocation_type nodeLocation): id(id), nodeLocation(nodeLocation) {};
		
		virtual int getId() {
			return id;
		};
		
		virtual NodeLocation_type getNodeLocation() {
			return nodeLocation;
		};

		virtual void setNodeLocation(NodeLocation_type nodeLocation_) {
			nodeLocation = nodeLocation_;
		};

		virtual double getLearnedCost() {return learnedCost;};

		virtual void setLearnedCost(double learnedCost_) {learnedCost = learnedCost_;};
};

#endif