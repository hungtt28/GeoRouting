/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GeoProtocolHelper.h"

GeoProtocol *getGeoProtocol(string protocolType) {
	if (protocolType.compare(_GPSR_) == 0) {
		return new GPSR();;
	}
	else if (protocolType.compare(_BOUNDHOLE_) == 0) {
		return new BoundHole();;
	}
	else {
		return new GeoProtocol();
	}
};