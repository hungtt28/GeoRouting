/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#ifndef GEOHELPER_H_
#define GEOHELPER_H_

#include "VirtualMobilityManager.h"

#ifndef M_PI
#define M_PI    3.1415926535897932384626433832795
#endif

#ifndef ZERO
#define ZERO 1e-10
#endif

struct Coord {
	double x;
	double y;
	double z;
	
	Coord(): x(0.0), y(0.0) {};
	Coord(double x, double y): x(x), y(y) {};

	inline bool operator==(const Coord& coord) {
		return x == coord.x && y == coord.y;
	}
	inline bool operator!=(const Coord& coord) {
		return !operator==(coord);
	}
};

double distance(NodeLocation_type node1, NodeLocation_type node2);

double getVectorAngle(NodeLocation_type vector);
double getAngle(NodeLocation_type node1, NodeLocation_type node2);
double getAngle(double angle1, double angle2);

double determinant(double a1, double a2, double b1, double b2);
bool intersectSections(NodeLocation_type begin1, NodeLocation_type end1, NodeLocation_type begin2, NodeLocation_type end2);

NodeLocation_type getCircumscribedcircleCenter(NodeLocation_type node1, NodeLocation_type node2, NodeLocation_type node3);

#endif /* GEOHELPER_H_ */
