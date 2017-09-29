// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Controls the objects in the world, insertion deletion and updating
// File:    WorldManager.cpp

#include "WorldManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "DisplayManager.h"

// Default constructor
df::WorldManager::WorldManager()
{
	setType("WorldManager");
	m_updates = *(new ObjectList());
	m_deletions = *(new ObjectList());
}

df::WorldManager& df::WorldManager::getInstance()
{
	static df::WorldManager instance;

	return instance;
}

int df::WorldManager::startUp()
{
	return Manager::startUp();
}

void df::WorldManager::shutDown()
{
	// Delete all game objects
	ObjectList ol = m_updates;	// copy list to delete by iteration
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
	{
		delete li.currentObject();
	}

	Manager::shutDown();
}

int df::WorldManager::insertObject(Object *p_o)
{
	return m_updates.insert(p_o);
}

int df::WorldManager::removeObject(Object *p_o)
{
	if (!m_updates.remove(p_o)) {
		delete p_o;
		return 0;
	}

	return 1;
}


df::ObjectList df::WorldManager::getAllObjects(bool inactive) const
{
	return m_updates;
}


df::ObjectList df::WorldManager::objectsOfType(std::string type) const
{
	ObjectList ol;
	ObjectListIterator li(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType().compare(type) == 0) {
			ol.insert(li.currentObject());
		}
	}

	return ol;
}


// Indicate Object is to be deleted at end of current game loop
// return 0 if successful
int df::WorldManager::markForDelete(Object *p_o)
{
	// Object might already be marked
	ObjectListIterator li(&m_deletions);
	while (!li.isDone()) {
		if (li.currentObject() == p_o) {
			return 0;
		}

		li.next();
	}

	m_deletions.insert(p_o);
	return 1;
}


// Update the world
void df::WorldManager::update()
{
	// Delete all marked objects
	ObjectListIterator liD(&m_deletions);
	while (!liD.isDone()) {
		delete liD.currentObject();
		liD.next();
	}

	m_deletions.clear();


	// Update object positions based on their velocities
	//Iterate through all objects
	ObjectListIterator liU(&m_updates);
	while (!liU.isDone()) {
		Object *p_temp_o = liU.currentObject();

		// Add velocity to position
		Vector new_pos = p_temp_o->predictPosition();

		// If object should change position then move it
		if(new_pos.getX() != p_temp_o->getPosition().getX() ||
			new_pos.getY() != p_temp_o->getPosition().getY()) {
			moveObject(p_temp_o, new_pos);
		}

		liU.next();
	}
}


void df::WorldManager::draw() {

	for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {
		ObjectListIterator li(&m_updates);
		while (!li.isDone()) {
			Object *p_temp_o = li.currentObject();
			if (p_temp_o->getAltitude() == alt) {
				p_temp_o->draw();
			}
			li.next();
		}
	}
}


df::ObjectList df::WorldManager::isCollision(Object *p_o, Vector where) const {
	ObjectList collisionList;

	// Iterate through all aobjects
	ObjectListIterator li(&m_updates);
	while (!li.isDone()) {
		Object *p_temp_o = li.currentObject();
		
		// Make sure it does not consider itself
		if (p_temp_o != p_o) {

			// Same location and both solid?
			if (posititonsIntersect(p_temp_o->getPosition(), where) && (p_temp_o->isSolid())) {
				collisionList.insert(p_temp_o);
			}

		}

		li.next();
	}

	return collisionList;
}


int df::WorldManager::moveObject(Object *p_o, Vector where) {
	if (p_o->isSolid()) {
		//Get Collisions
		ObjectList list = isCollision(p_o, where);

		if (!list.isEmpty()) {
			
			bool do_move = true; // Assume cna move

			// Iterate over list
			ObjectListIterator li(&list);
			while (!li.isDone()) {
				Object *p_temp_o = li.currentObject();
				
				// Create collison event
				EventCollision c(p_o, p_temp_o, where);

				// Send to both objects
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				// If both Hard, then cannot move
				if ((p_o->getSolidness() == HARD) && (p_temp_o->getSolidness() == HARD)) {
					do_move = false; // Cant move
				}

				li.next();
			}
			
			if (do_move == false) {
				return -1;
			}
		}
	}

	// Move
	p_o->setPosition(where);

	// Check if object has moved out of bounds
	if (p_o->getPosition().getX() < 0 ||
		p_o->getPosition().getX() > DM.getHorizontal() ||
		p_o->getPosition().getY() < 0 ||
		p_o->getPosition().getY() > DM.getVertical()) {

		// Generate out of Bounds event and send to Object
		EventOut ov;
		p_o->eventHandler(&ov);
	}
	

	return 0;
}



int df::WorldManager::onEvent(const Event *p_event) const {
	return Manager::onEvent(p_event);
}