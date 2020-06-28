EXE = game

CXXFILES = $(shell find src -maxdepth 1 -type f -name '*.cpp')
CXXOBJECTS = $(CXXFILES:.cpp=.o)

CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lncurses

INCLUDE = 

SOURCES = $(CXXFILES)
OBJECTS = $(CXXOBJECTS)


##################################################################
# Got it from = https://github.com/alexdantas/sdl2-platformer/blob/master/Makefile
#
# This is a Makefile progress indicator.
# I couldn't understand how it was done - simply copied here.

# BUILD is initially undefined
ifndef BUILD

# max equals 256 x's
sixteen := x x x x x x x x x x x x x x x x
MAX := $(foreach x,$(sixteen),$(sixteen))

# T estimates how many targets we are building by replacing BUILD with
# a special string
T := $(shell $(MAKE) -nrRf $(firstword $(MAKEFILE_LIST)) $(MAKECMDGOALS) \
            BUILD="COUNTTHIS" | grep -c "COUNTTHIS")

# N is the number of pending targets in base 1, well in fact, base x
# :-)
N := $(wordlist 1,$T,$(MAX))

# auto-decrementing counter that returns the number of pending targets
# in base 10
counter = $(words $N)$(eval N := $(wordlist 2,$(words $N),$N))

# BUILD is now defined to show the progress, this also avoids
# redefining T in loop
BUILD = @echo $(counter) of $(T)
endif
###################################################################

all: $(EXE)
	# Build Successfull

$(EXE): $(OBJECTS)
	# Linking ...
	$(MUTE)$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $< ...
	$(MUTE)$(CXX) $(CXXFLAGS) $(INCLUDE) $< -c -o $@
	$(BUILD)

run: all
	$(MUTE)./$(EXE)

clean:
	# Cleaning
	-$(MUTE)rm -f $(EXE) $(OBJECTS)
