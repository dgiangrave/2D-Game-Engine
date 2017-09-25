// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Controls the objects in the world, insertion deletion and updating
// File:    WorldManager.cpp

#include "WorldManager.h"

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


df::ObjectList df::WorldManager::getAllObjects() const
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
void df::WorldManager::upddate()
{
	// Delete all marked objects
	ObjectListIterator li(&m_deletions);
	while (!li.isDone()) {
		delete li.currentObject();
		li.next();
	}

	m_deletions.clear();
}