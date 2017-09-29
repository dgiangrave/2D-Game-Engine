// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Contains utility methods that should not reside in specific classes
// File:    utility.cpp

#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "utility.h"

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