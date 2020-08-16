#include <ncurses.h>

#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState()
{ }

void MenuState::Update(float)
{
}

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
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("#----- Snake -----#");
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("By: Sebastian Olsson");
	i++;
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("To Start press 'ENTER'");
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("To Quit press 'Q'");
}

