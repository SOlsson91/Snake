#include <unistd.h>
#include "./Game.h"
#include "./MenuState.h"
#include "./GameState.h"

std::unique_ptr<StateMachine> Game::stateMachine { std::make_unique<StateMachine>() };
bool Game::s_IsRunning = true;
unsigned int Game::s_Score = 0;

Game::Game()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();
	stateMachine->PushState(std::make_unique<MenuState>());
}

Game::~Game()
{
	endwin();
}

void Game::Run()
{
	if (!has_colors())
	{
		printw("Terminal does not support color");
		s_IsRunning = false;
	}
	while (s_IsRunning)
	{
		stateMachine->Render();
		stateMachine->ProcessInput();
		stateMachine->Update(0.0f);
		Sleep();
	}
}

void Game::Sleep()
{
	refresh();
	usleep(m_UpdatedPerSec * CONVERT_TO_SECONDS);
}
