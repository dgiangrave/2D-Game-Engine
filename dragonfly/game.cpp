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

#include "Hero.h"
#include "Star.h"
#include "Saucer.h"

void populateWorld(void);

int main(int argc, char *argv[]) {
	
	GM.startUp();
	
	LM.setFlush(true);
	

	populateWorld();

	GM.run();


  // Show splash screen.
  //df::splash();

  // Shut everything down.
	GM.shutDown();


}

// Populate world with some objects.
void populateWorld(void) {

	// Spawn some Stars.
	for (int i = 0; i<16; i++)
		new Star;

	// Create hero.
	new Hero;

	// Spawn some saucers to shoot.
	for (int i = 0; i<16; i++)
		new Saucer;
}