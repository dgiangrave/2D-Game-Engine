// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Header file for utility methods
// File:    utility.h

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Vector.h"

namespace df {

	// Returns pretty-formatted time as char * string
	char *getTimeString();

	// Return true if teo positions intersecct, else false
	bool posititonsIntersect(Vector p1, Vector p2);

} // End of df namespace
#endif // __UTILITY_H__