// Author:  David Giangrave
// Date:    9/13/17
// Purpose: The generic object class for an object in the game world
// File:    Object.cpp

#include <string>

#include "Object.h"
#include "Vector.h"
#include "WorldManager.h"

// Construct object. Set default params and
// add to game world (WorldManager)
df::Object::Object()
{
	// Add self to game world
	df::WorldManager::getInstance().insertObject(this);

	static int id_counter;
	id = id_counter++;
	type = "Object";
	position = *(new Vector);
}

// Destroy object
// remove from game world (WorldManager)
df::Object::~Object()
{
	// Add self to game world
	df::WorldManager::getInstance().removeObject(this);
}

// set Object id
void df::Object::setId(int new_id) {
	id = new_id;
}

// get object id
int df::Object::getId() const {
	return id;
}

// set type identifier of object
void df::Object::setType(std::string new_type) {
	type = new_type;
}

// Get type identifier of object
std::string df::Object::getType() const {
	return type;
}

// set position of object
void df::Object::setPosition(Vector new_pos) {
	position = new_pos;
}

// get position of object
df::Vector df::Object::getPosition() const {
	return position;
}

int df::Object::eventHandler(const Event *p_e) {
	return 0;
}

void df::Object::draw() {
	//return;
}

int df::Object::setAltitude(int new_altitude) {
	m_altitude = new_altitude;
	return 0;
}

int df::Object::getAltitude() const {
	return m_altitude;
}