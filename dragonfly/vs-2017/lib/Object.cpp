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

df::Vector df::Object::predictPosition() {
	// Add velocity to position
	Vector new_pos = position + getVelocity();

	return new_pos;
}

void df::Object::setSpeed(float new_speed) {
	speed = new_speed;
}

float df::Object::getSpeed() const {
	return speed;
}

void df::Object::setDirection(Vector newDirection) {
	direction = newDirection;
}

df::Vector df::Object::getDirection() const {
	return direction;
}

void df::Object::setVelocity(Vector new_velocity) {
	speed = new_velocity.getMagnitude();
	direction = new_velocity;
	direction.normalize();
}

df::Vector df::Object::getVelocity() const {
	Vector vel;
	vel = direction;
	vel.scale(speed);

	return vel;
}

bool df::Object::isSolid() const {
	if (m_solidness == HARD || m_solidness == SOFT) {
		return true;
	}
	else {
		return false;
	}
}

int df::Object::setSolidness(Solidness new_solid) {
	m_solidness = new_solid;
	return 0;
}

df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}