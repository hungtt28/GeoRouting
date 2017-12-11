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


enum GPSRForwardingMode {
    GPSR_GREEDY_ROUTING = 0;
    GPSR_PERIMETER_ROUTING = 1;
};

packet GPSRPacket extends GeoRoutingPacket {			// new packet must inherit from GeoRoutingPacket
    int routingMode = GPSR_GREEDY_ROUTING;		// M
	NodeLocation_type destinationLocation;		// D	- destination has beed defined in GeoRoutingPacket, let this to clear GPSR packet definition
	NodeLocation_type startPerimeterLocation;	// Lp
	NodeLocation_type forwardPerimeterLocation;	// Lf
	string firstSenderAddress;					// e0
	string firstReceiverAddress;				// e0
	string senderAddress;
}

