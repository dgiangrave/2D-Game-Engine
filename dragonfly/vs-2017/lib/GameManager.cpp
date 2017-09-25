// Author:  David Giangrave
// Date:    9/13/17
// Purpose: The game manager starts up all game engine services as well as
//          processes the game loop, sleeping if needed
// File:    GameManager.cpp

#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "WorldManager.h"
#include "ObjectList.h"

#include <Windows.h>

// Set default fields
df::GameManager::GameManager()
{
	setType("GameManager");
	game_over = true;
	frame_time = FRAME_TIME_DEFAULT;
}

// Get the singleton instance of GameManager
df::GameManager& df::GameManager::getInstance()
{
	static df::GameManager instance;

	return instance;
}

// Set game over status to indicated value
// if true (default), will stop game loop
void df::GameManager::setGameOver(bool new_game_over)
{
	game_over = true;
}

// Get game over status
bool df::GameManager::getGameOver() const
{
	return game_over;
}

// Return frame time
// Frame time is target time for game loop, in milliseconds
int df::GameManager::getFrameTime() const
{
	return frame_time;
}

// Starts up all other managers in proper order
int df::GameManager::startUp()
{
	df::Manager::startUp();

	df::LogManager& log_manager = df::LogManager::getInstance();
	if (log_manager.startUp() != 0) {
		return 1;
	}
	log_manager.writeLog("### Log Manager Started Up ###");

	df::WorldManager& world_manager = df::WorldManager::getInstance();
	if (world_manager.startUp() != 0) {
		return 1;
	}

	game_over = false;
	frame_time = 33;

	return 0;
}

// Shutdown all GameManager services
void df::GameManager::shutDown()
{
	df::Manager::shutDown();

	df::LogManager& log_manager = df::LogManager::getInstance();
	log_manager.writeLog("### Log Manager Shutting Down ###");
	log_manager.shutDown();

	game_over = true;
}

// The game loop
void df::GameManager::run()
{
	Clock clock;
	ObjectList world_objects;
	while (!game_over)
	{
		clock.delta();
		// ----- Get input -----

		// ----- Update Game world state -----
		/*
		// Have objects update themselves
		ObjectListIterator li(&world_objects);
		for (li.first(); !li.isDone(); li.next())
		{
			li.currentObject()->Update();
		}

		// Move all objects
		for (li.first(); !li.isDone(); li.next())
		{
			WorldManager move(li.currentObject());
		}

		// Draw all objects
		for (li.first(); !li.isDone(); li.next())
		{
			WorldManager draw(li.currentObject());
		}
		*/
		// ----- Draw current scene to back buffer -----

		// ----- Swap back buffer to current buffer -----

		// ----- Sleep if needed -----
		int sleep_time = (getFrameTime() - clock.split());
		Sleep(sleep_time);


		// Record messege of game loop to the log
		//df::LogManager& log_manager = df::LogManager::getInstance();
		//log_manager.writeLog("Full game loop processed");
	}
}