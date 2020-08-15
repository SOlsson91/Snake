#include <ncurses.h>

#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState()
{ }

MenuState::~MenuState()
{ }

void MenuState::OnEnter()
{
}

void MenuState::OnExit()
{
}

void MenuState::Update(float dt)
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
		Game::stateMachine->PushState(std::unique_ptr<State>(new GameState));
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

