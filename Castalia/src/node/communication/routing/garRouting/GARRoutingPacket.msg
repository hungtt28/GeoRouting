//
// Copyright (C) 2013 Opensim Ltd
// Author: Levente Meszaros
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

cplusplus {{
#include "GeoRoutingPacket_m.h"
#include "VirtualMobilityManager.h"
}}

class GeoRoutingPacket;
struct NodeLocation_type;

enum GARForwardingMode {
    GAR_GREEDY_ROUTING = 0;
    GAR_GAR_ROUTING = 1;
};

packet GARRoutingPacket extends GeoRoutingPacket {
    int routingMode = GAR_GREEDY_ROUTING;    // M
	NodeLocation_type destinationLocation;      // D
	NodeLocation_type startPerimeterLocation;	// Lp
	NodeLocation_type forwardPerimeterLocation;	// Lf
	string firstSenderAddress;					// e0
	string firstReceiverAddress;				// e0
	string senderAddress;
}


