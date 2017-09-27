//
// Star.cpp
//

// System includes.
#include <stdlib.h>		// for rand()

// Engine includes.
#include "DisplayManager.h"
#include "WorldManager.h"

// Game includes.
#include "Star.h"

Star::Star() {
	setType("Star");
	setAltitude(0);
	df::Vector p((float)(rand() % (int)DM.getHorizontal()),
		(float)(rand() % (int)DM.getVertical()));
	setPosition(p);
}

// Draw star on window.
void Star::draw() {
	DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

// Handle event.
// Return 0 if ignored, else 1.
int Star::eventHandler(const df::Event *p_e) {

	// If get here, have ignored this event.
	return 0;
}
