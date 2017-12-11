/*
 * WSN Geographic Routing base on Castialia/Omnetpp
 *
 *  Created on: Nov 3, 2017
 *      Author: hungtt28
 */

#include "GeoHelper.h"


double distance(NodeLocation_type node1, NodeLocation_type node2) {
	return sqrt((node1.x - node2.x) * (node1.x - node2.x) + (node1.y - node2.y) * (node1.y - node2.y));
}

//
// angle
//

double getVectorAngle(NodeLocation_type vector)
{
    // double angle = atan2(-vector.y, vector.x);
	double angle = atan2(vector.y, vector.x);
    if (angle < ZERO)
        angle += 2 * M_PI;
    return angle;
}

double getAngle(NodeLocation_type node1, NodeLocation_type node2)
{
	NodeLocation_type vector;
	vector.x = node2.x - node1.x;
	vector.y = node2.y - node1.y;
    return getVectorAngle(vector);
}

double getAngle(double angle1, double angle2) {
	double angle = angle2 - angle1;
	if (angle < ZERO)
		angle += 2 * M_PI;
	return angle;
}

double determinant(double a1, double a2, double b1, double b2) {
	return (a1 * b2 - a2 * b1);
}

bool intersectSections(NodeLocation_type begin1, NodeLocation_type end1, NodeLocation_type begin2, NodeLocation_type end2)
{
    double x1 = begin1.x;
    double y1 = begin1.y;
    double x2 = end1.x;
    double y2 = end1.y;
    double x3 = begin2.x;
    double y3 = begin2.y;
    double x4 = end2.x;
    double y4 = end2.y;
    double a = determinant(x1, y1, x2, y2);
    double b = determinant(x3, y3, x4, y4);
    double c = determinant(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
    double x = determinant(a, x1 - x2, b, x3 - x4) / c;
    double y = determinant(a, y1 - y2, b, y3 - y4) / c;
    if (
	((x1 < x && x < x2) || (x1 > x && x > x2)) && 
	((x3 < x && x < x4) || (x3 > x && x > x4)) && 
	((y1 < y && y < y2) || (y1 > y && y > y2)) && 
	((y3 < y && y < y4) || (y3 > y && y > y4)))
        return true;
    else
        return false;
}

// https://en.wikipedia.org/wiki/Circumscribed_circle
NodeLocation_type getCircumscribedcircleCenter(NodeLocation_type A, NodeLocation_type B, NodeLocation_type C) {
	
	double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
	
	double Ux = (1 / D) * ((A.x*A.x + A.y*A.y)*(B.y - C.y) + (B.x*B.x + B.y*B.y)*(C.y - A.y) + (C.x*C.x + C.y*C.y) * (A.y - B.y));
	
	double Uy = (1 / D) * ((A.x*A.x + A.y*A.y)*(C.x - B.x) + (B.x*B.x + B.y*B.y)*(A.x - C.x) + (C.x*C.x + C.y*C.y) * (B.x - A.x));
	
	NodeLocation_type centerLocation;
	centerLocation.x = Ux;
	centerLocation.y = Uy;
	
	return centerLocation;
}