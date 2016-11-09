# General
* Figure out how to document members
* Add text to buttons
* Add quadtrees to collision detection
* Cache PhysicsObject::getPointsGlobal
* Update util::getRandom to use c++11 random library
* Add proper physics, what you are doing now is crazy   xf += v*t      vf += a*t     a=F/m    and use forces to move

# Code Cleanup
* Split crate MainMenu.tpp and move templates there
* Figure out how to document template parameters. Look into Boost QuickBook?
* Move as many of the includes from the hpp files to the cpp files as possible
* Remove TODO's from code.
* Maybe move all the brickbreaker specific stuff into a namespace? Ball, Paddle, Wall, BrickBreaker, etc.

# Game Modes
* Brick Breaker
* Alien Invaders
* Snake

# Reference/Reading
* http://www.gamasutra.com/view/feature/1630/breaking_down_breakout_system_and_.php?print=1