cmake_minimum_required(VERSION 3.2)
project(game)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -Wshadow -Wpedantic -O3 -g")
#-Wconversion

file(GLOB SOURCE
	"./src/*.c"
	"./src/*.h"
	"./src/*.cpp"
	"./src/*.hpp"
)

add_executable(game ${SOURCE})

target_link_libraries(game 
	-lcurses
	-lmenu
)
