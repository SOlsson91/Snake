#include <unistd.h>
#include "./Game.h"
#include "./MenuState.h"
#include "./GameState.h"


std::unique_ptr<StateMachine> Game::stateMachine = std::make_unique<StateMachine>();
bool Game::s_IsRunning = true;

Game::Game()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();

	stateMachine->PushState(std::unique_ptr<State>(new MenuState));
}

Game::~Game()
{
	endwin();
}

void Game::Run()
{
	while (s_IsRunning)
	{
		Render();
		GetInput();
		Update();
		Sleep();
	}
}

void Game::Sleep()
{
	refresh();
	usleep(m_UpdatedPerSec * CONVERT_TO_SECONDS);
}

void Game::Render()
{
	stateMachine->Render();
}

void Game::GetInput()
{
	stateMachine->ProcessInput();
}

void Game::Update()
{
	stateMachine->Update(0.0f);
}
