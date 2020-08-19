#include <ncurses.h>

#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState()
{}

void MenuState::Render()
{
	DrawInfo();
}

void MenuState::ProcessInput()
{
	int key = getch();
	switch (key)
	{
	case 10: //ENTER
		Game::stateMachine->PopState();
		Game::stateMachine->PushState(std::make_unique<GameState>());
		break;
	case 'q': 
		Game::s_IsRunning = false;
		break;
	}
}

void MenuState::DrawInfo()
{
	int i = 0;
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "#----- Snake -----#");
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "By: Sebastian Olsson");
	i++;
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "To Start press 'ENTER'");
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "To Quit press 'Q'");
}

