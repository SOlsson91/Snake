#pragma once

#include "Game.h"
#include "StateMachine.h"
#include "Constants.h"

#include <curses.h>
#include <menu.h>

class EndState : public State
{
private:
	const int MAP_WIDTH = 60;
	const int MAP_HEIGHT = 10;
	const char* replay = "Replay";
	const char* quit = "Quit";
	int m_Highlight = 0;

	std::unique_ptr<WINDOW> m_Window;
	Game* m_Game;

public:
	EndState(Game* game);
	~EndState();
	void Render() override;
	void ProcessInput() override;
};
