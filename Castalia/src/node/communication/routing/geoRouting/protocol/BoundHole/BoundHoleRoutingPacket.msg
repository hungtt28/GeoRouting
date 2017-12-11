//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

cplusplus {{
#include "GeoRoutingPacket_m.h"
#include "VirtualMobilityManager.h"
}};

class GeoRoutingPacket;
struct NodeLocation_type;


enum BoundHoleForwardingMode {
    BOUNDHOLE_GREEDY_ROUTING = 0;
    BOUNDHOLE_BOUNDHOLE_ROUTING = 1;
};

packet BoundHoleRoutingPacket extends GeoRoutingPacket {			// new packet must inherit from GeoRoutingPacket
    int routingMode = BOUNDHOLE_GREEDY_ROUTING;		// M
	NodeLocation_type destinationLocation;		// D
	NodeLocation_type startBoundHoleLocation;	// Lp
	int startIngressId = -1;
	int startBoundHoleId = -1;
	int holeId = -1;
}

