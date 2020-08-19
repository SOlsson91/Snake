#pragma once

#include "Game.h"
#include "StateMachine.h"

class EndState : public State
{
private:
	const int MAP_WIDTH = 60;
	const int MAP_HEIGHT = 10;
	const char* replay = "Replay";
	const char* quit = "Quit";
	int m_Highlight = 0;

	WINDOW* m_Window;
	enum MENU_OPTIONS
	{
		START = 0,
		EXIT = 1
	};

public:
	EndState();
	void Render() override;
	void ProcessInput() override;
};
