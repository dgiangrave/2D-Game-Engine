//
// game.cpp
// 

#include <stdarg.h>
#include <stdio.h>

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "TestClass.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "Object.h"
#include "DisplayManager.h"

#include "Star.h"

int main(int argc, char *argv[]) {
	
	df::GameManager &game_manager = df::GameManager::getInstance();
	game_manager.startUp();
	
	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.setFlush(true);
	
	/*
	// Add 3 TestClass Objects to the game world with varying locations
	df::TestClass* tc0 = new df::TestClass;
	df::TestClass* tc1 = new df::TestClass;
	df::TestClass* tc2 = new df::TestClass;

	// Print out the current three objects in the world
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::ObjectList ol = world_manager.getAllObjects();
	df::ObjectListIterator li(&ol);
	log_manager.writeLog("The World contains the following TestClass");
	for (li.first(); !li.isDone(); li.next())
	{
		log_manager.writeLog("TestClass id: %d", li.currentObject()->getId());
	}

	// Add 2 more TestClass objects to the world
	df::TestClass* tc3 = new df::TestClass;
	df::TestClass* tc4 = new df::TestClass;

	// Print out all objects in the game world
	df::ObjectList ol2 = world_manager.getAllObjects();
	df::ObjectListIterator li2(&ol2);
	log_manager.writeLog("The World contains the following TestClass");
	for (li2.first(); !li2.isDone(); li2.next())
	{
		log_manager.writeLog("TestClass id: %d", li2.currentObject()->getId());
	}

	// Mark tc1 and tc3 for deletion and remove tc2
	// The objects marked for deletion will still show up seeing as the game loop is not running
	// while the removed object will disapear from the game world!
	world_manager.markForDelete((df::Object *)tc1);
	world_manager.markForDelete((df::Object *)tc3);
	world_manager.removeObject((df::Object *)tc2);

	
	// Print out all objects in the game world
	df::ObjectList ol3 = world_manager.getAllObjects();
	df::ObjectListIterator li3(&ol3);
	log_manager.writeLog("The World contains the following TestClass");
	for (li3.first(); !li3.isDone(); li3.next())
	{
		log_manager.writeLog("TestClass id: %d", li3.currentObject()->getId());
	}
	*/

	new Star;
	new Star;
	new Star;
	new Star;

	game_manager.run();

	

	/*
  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }
  */
  

  // Set flush of logfile during development (when done, make false).
  //LM.setFlush(true);

  // Show splash screen.
  //df::splash();

  // Shut everything down.
  //GM.shutDown();
	game_manager.shutDown();


}

