/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "NeighborTable.h"

void NeighborTable::update(NeighborRecord *neighborRecord) {
	
	int recordIndex = -1;
	for (int i = 0; i < neighborTable.size(); i++) {
		if (neighborTable[i]->getId() == neighborRecord->getId()) {
			recordIndex = i;
			break;
		}
	}
	
	if (recordIndex == -1) {
		// add new neighbor record
		neighborTable.push_back(neighborRecord);
	}
	else {
		delete neighborRecord;
	}
}

NeighborRecord* NeighborTable::getRecord(int i) {
	return neighborTable[i];
}

int NeighborTable::getNeighborIndex(int id) {
	
	int recordIndex = -1;
	for (int i = 0; i < neighborTable.size(); i++) {
		if (neighborTable[i]->getId() == id) {
			recordIndex = i;
			break;
		}
	}
	
	return recordIndex;
}