# Snake
Simple snake game created with ncurses

## Requirements
The project is created with [ncurses](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/).
To build the project you need [CMake](https://cmake.org) V3.2 or later.

## Build & Run
    * mkdir build
    * cd build
    * cmake ..
    * make -j${nproc}
    * ./game


## Controls
### Menu
You can navigate both menus with the arrow keys, and enter to select the highlighted option.

### Game
Arrow keys to change direction, or W,A,S,D. 

![Image of the Snake game](https://github.com/SOlsson91/Snake/blob/master/img/snake.png)

## TODO
    * Refactoring
	* Improve the UI
	* Implement HighScore
	* Make the game window depend on the terminal window
