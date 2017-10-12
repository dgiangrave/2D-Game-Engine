//
// game.cpp
// 

#include <stdarg.h>
#include <stdio.h>

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "Object.h"
#include "DisplayManager.h"



int main(int argc, char *argv[]) {
	
	GM.startUp();
	
	LM.setFlush(true);
	

	GM.run();


  // Show splash screen.
  //df::splash();

  // Shut everything down.
	GM.shutDown();


}
