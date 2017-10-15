Dragonfly
David Giangrave
dlgiangrave
dlgiangrave@wpi.edu
10-14-2017

--------------------------------------------------------------------

To build:

IMPORTANT!
--- Build Environment: Windows 64 bit Visual Studio ---

0) Setup development environment for Windows
See http://dragonfly.wpi.edu/engine/index.html#setup for details.

Note: This only works when the project folder is placed in the same
directory as SFML-2.4

1) Build, F7 on Windows from Visual Studio.

2) Run game, F5 on Windows from Visual Studio.

--------------------------------------------------------------------

Directories:

vs-2015/ - contains Visual Studio solution files (Microsoft Windows)
vs-2015/include - contains dragonfly header files
vs-2015/include/saucershoot - contains saucer shoot example headers
vs-2015/lib - contains dragonfly cpp files
vs-2015/lib/saucershoot - contains saucershoot example cpp files

/*
NOTE: you must have proper linkage to all above locations for
      this to run, this does not use the default dragonfly setup
      links but it should work with the relative paths
*/

sounds/ - contains sound files for saucershoot example
sprites/ - contains sprites for saucershoot example
../SFML-2.4 - Contains SFML outside of dragonflys directory
../SFML-2.4/include - SFML header files
../SFML-2.4/lib - SFML library files

--------------------------------------------------------------------

Testing Example:

I used the dragonfly saucer shoot example from Professor Claypools
github to show the bulk of my testing. It properly shows use of all
the engines current functionality without any bugs. Do note however
that some minor modifications were made to the example based on bugs
in Professor Claypools code. This was things like only sending out
event to stars that went off left side rather than right side.


--------------------------------------------------------------------

Please contact me with any questions or issues with the build.

David Giangrave
dlgingrave@wpi.edu