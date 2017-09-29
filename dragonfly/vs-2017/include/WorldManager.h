// Author:  David Giangrave
// Date:    9/13/17
// Purpose: Header file for world manager class
// File:    WorldManager.h

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

// Two-letter acronym for easier access to manager
#define WM df::WorldManager::getInstance()


namespace df {

	const int MAX_ALTITUDE = 4;

	class WorldManager : Manager {


	private:
		WorldManager(); // singleton
		WorldManager(WorldManager const&); // Don't allow copy
		void operator=(WorldManager const&); // sont allow assignment
		

		ObjectList m_updates;  // All objects in the world to update
		ObjectList m_deletions; // All objects to be deleted

	public:
		// Get a signle instance
		static WorldManager &getInstance();

		// Startup game world by initializing everything
		int startUp();

		// Shutdown everything delete it all
		void shutDown();

		// inset objects into the world. return 0 if successful
		int insertObject(Object *p_o);

		// remove object from world return 0 if successful
		int removeObject(Object *p_o);

		// return list of all Objects in world
		ObjectList getAllObjects(bool inactive = false) const;

		// return list of all Objexts in world matching type
		ObjectList objectsOfType(std::string type) const;

		//update world
		// Delete objects marked for deletion
		void update();

		// Indicate Object is to be deleted at end of current game loop
		// return 0 if successful
		int markForDelete(Object *p_o);

		void draw(); // Call draw method on all objects in the world

		// Return list of Objects colllises with at position 'where'
		// Collisions only solid objects
		// Does not consider if p_o is solid or not
		ObjectList isCollision(Object *p_o, Vector where) const;

		// Move Object
		// If collidion with solid send collision events
		// if no collision eith solid move ok, else dont move object
		// if object is Spectral, move ok
		// Return 0 if moved okay, else -1 if collided with a solid
		int moveObject(Object *p_o, Vector where);

		// Send event to all Objects
		// Return count of number  of events sent
		int onEvent(const Event *p_event) const;

	};

} // End df namespace
#endif // __WORLD_MANAGER_H__