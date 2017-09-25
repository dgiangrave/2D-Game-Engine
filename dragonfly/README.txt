Dragonfly Egg
David Giangrave
dlgiangrave
dlgiangrave@wpi.edu
9-13-2017

--------------------------------------------------------------------

To build:

IMPORTANT!
--- Build Environment: Windows 64 bit Visual Studio ---

0) Setup development environment for Windows
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

Note: This only works when the project folder is placed in the same
directory as SFML

1) Build, F7 on Windows from Visual Studio).

2) Run game, F5 on Windows from Visual Studio)

--------------------------------------------------------------------

Directories:

vs-2015/ - contains Visual Studio solution files (Microsoft Windows)

--------------------------------------------------------------------

Testing Example:

I have implemented a TestClass object that acts like an ordinary 
object in the game world but reads everything to the log.
The way the example is run is displayed below.

1) Create 3 different TestClass objects, adding them to the game 
   world at different locations. Have them print these locations
   along with their ID to dragonfly.log

2) Print out a list of all Test Class objects in the world.
   This should only be number 0, 1, and 2

3) Add 2 more objects repeating the steps above

4) Mark 2 objects for deleation and remove one from the world
   The ones marked for  deletion will remain because this example
   happens outside the game loop. The removed one however will
   be removed from the game world and will not show up.

5) Print out all world objects again to see the above expected
   results


--------------------------------------------------------------------

Please contact me with any questions or issues with the build.

David Giangrave
dlgingrave@wpi.edu


