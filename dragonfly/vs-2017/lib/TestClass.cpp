// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Provides examples of functionality for dragonfly egg
// File:    TestClass.cpp


#include "TestClass.h"
#include "LogManager.h"
#include "Vector.h"

df::TestClass::TestClass(){
	setType("TestClass");
	LM.writeLog("TestClass%d has been created as an object in the game world!", this->getId());
	LM.writeLog("TestClass%d has an object id of: %d", this->getId(), this->getId());

	// Set the position of this test object to 10, 10 in the game world
	// then print it out
	Vector vec2 = *(new Vector);
	static int posCounter = 0;
	posCounter += 10;
	vec2.setX(posCounter);
	vec2.setY(posCounter);
	setPosition(vec2);
	LM.writeLog("TestClass%d position: (%f,%f)", this->getId(), vec2.getX(), getPosition().getY());
}

df::TestClass::~TestClass() {
	LM.writeLog("TestClass%d has been deleted from the game world!", this->getId());
}

void df::TestClass::draw() {

}

