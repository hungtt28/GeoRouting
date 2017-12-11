/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _NEIGHBORTABLE_H_
#define _NEIGHBORTABLE_H_

#include "NeighborRecord.h"
#include "VirtualMobilityManager.h"

class NeighborTable {
	private:
		vector<NeighborRecord*> neighborTable;
	public:
		virtual void update(NeighborRecord *neighborRecord);
		
		int size() {
			return neighborTable.size();
		}
		
		NeighborRecord* getRecord(int i);
		int getNeighborIndex(int id);
};

#endif