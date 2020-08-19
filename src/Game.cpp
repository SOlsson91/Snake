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

	//raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	//m_Window = 
	stateMachine->PushState(std::make_unique<MenuState>());
}

Game::~Game()
{
	endwin();
}

void Game::Run()
{
	while (s_IsRunning)
	{
		clear();
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
