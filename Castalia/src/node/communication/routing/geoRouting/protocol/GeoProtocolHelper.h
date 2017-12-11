/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */
 
#ifndef _GEOPROTOCOLHELPER_H_
#define _GEOPROTOCOLHELPER_H_

#include "GeoProtocol.h"
#include "NeighborTable.h"
#include "GeoHelper.h"
#include "VirtualMobilityManager.h"

#include "GPSR.h"
#define _GPSR_ "GPSR"

#include "BoundHole.h"
#define _BOUNDHOLE_ "BoundHole"


GeoProtocol *getGeoProtocol(string protocolType);

#endif