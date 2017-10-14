// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Contains utility methods that should not reside in specific classes
// File:    utility.cpp

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <sstream>

#include "utility.h"
#include "LogManager.h"
#include "WorldManager.h"

using std::stringstream;

// Return a nicely-formatted time string HH:MM:SS
char *df::getTimeString()
{
	// String to return, made 'static' so persists
	static char time_str[30];

	// System calls to get Time
	time_t now;
	time(&now);
	struct tm *p_time = localtime(&now);

	// '02' gives two digits, '%d' for integers
	sprintf(time_str, "%02d:%02d:%02d",
		p_time->tm_hour,
		p_time->tm_min,
		p_time->tm_sec);

	return time_str;
}


bool df::posititonsIntersect(Vector p1, Vector p2) {
	if ((abs(p1.getX() - p2.getX()) <= 1) &&
		(abs(p1.getY() - p2.getY()) <= 1)) {
		return true;
	}
	else {
		return false;
	}
}


bool df::boxIntersectsBox(Box A, Box B) {

	bool x_overlap = false, y_overlap = false;
	int Ax1 = A.getCorner().getX(),
		Ax2 = A.getCorner().getX() + A.getHorizontal() - 1,
		Ay1 = A.getCorner().getY(),
		Ay2 = A.getCorner().getY() + A.getVertical() - 1,
		Bx1 = B.getCorner().getX(),
		Bx2 = B.getCorner().getX() + B.getHorizontal() - 1,
		By1 = B.getCorner().getY(),
		By2 = B.getCorner().getY() + B.getVertical() - 1;

	// Test horizontal overlap
	if ((Bx1 <= Ax1 && Ax1 <= Bx2) // either left side of A in B
		|| (Ax1 <= Bx1 && Bx1 <= Ax2)) { //or left side of B in A

		x_overlap = true;
	}
	// Test vertical overlap
	if ((By1 <= Ay1 && Ay1 <= By2) // either top side of A in B
		|| (Ay1 <= By1 && By1 <= Ay2)) { //or top side of B in A
		y_overlap = true;
	}


	if ((x_overlap) && (y_overlap)) {
		return true;
	}
	else {
		return false;
	}
}


df::Box df::getWorldBox(const Object *p_o) {
	Box temp_box = p_o->getBox();
	Vector corner = temp_box.getCorner();

	temp_box = getWorldBox(p_o, p_o->getPosition());

	return temp_box;
}

df::Box df::getWorldBox(const Object *p_o, Vector where) {
	Box temp_box = p_o->getBox();
	Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);

	return temp_box;

}


df::Vector df::worldToView(Vector world_pos) {
	Vector view_origin = WM.getView().getCorner();

	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}


df::Vector df::viewToWorld(Vector world_pos) {
	Vector view_origin = WM.getView().getCorner();

	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);

	return view_pos;
}


std::string df::toString(int i) {
	std::stringstream ss;	//create stringstream
	ss << i;;				//Add a number to stream.
	return ss.str();		//Return string with contents of stream
}