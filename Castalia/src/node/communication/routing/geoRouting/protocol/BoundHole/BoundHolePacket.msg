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
#include "GeoControlPacket_m.h"
#include "VirtualMobilityManager.h"

struct Node {
	int nodeId;
	NodeLocation_type nodeLocation;
	
	Node(){};
	Node(int id, NodeLocation_type nodeLocation): nodeId(id), nodeLocation(nodeLocation) {};
};

typedef std::vector<Node> Nodes;
}};

class GeoControlPacket;
struct NodeLocation_type;
struct Node;
class noncobject Nodes;


enum BoundHoleMode {
    BOUNDHOLE_SUPPRESSED_START_MODE = 0;
	BOUNDHOLE_REFRESH_MODE = 1;
};

packet BoundHolePacket extends GeoControlPacket {
    int boundHoleMode = BOUNDHOLE_SUPPRESSED_START_MODE;
	int originalId = -1;
	int holeId = -1;
	bool bForce = false;
	int iNode = -1;
	Nodes boundHoleNodes;
}

