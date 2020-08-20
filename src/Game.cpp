#include <unistd.h>
#include "./Game.h"
#include "./MenuState.h"
#include "./GameState.h"

Game::Game()
	: m_StateMachine(std::make_shared<StateMachine>()), m_IsRunning(true), m_Score(0)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();
	m_StateMachine->PushState(std::make_unique<MenuState>(this));
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
		m_IsRunning = false;
	}
	while (m_IsRunning)
	{
		m_StateMachine->Render();
		m_StateMachine->ProcessInput();
		m_StateMachine->Update(0.0f);
		Sleep();
	}
}

void Game::Sleep()
{
	refresh();
	usleep(m_UpdatedPerSec * CONVERT_TO_SECONDS);
}

std::shared_ptr<StateMachine> Game::GetStateMachine() const
{
	return m_StateMachine;
}

bool Game::GetIsRunning() const
{
	return m_IsRunning;
}

void Game::SetIsRunning(bool running)
{
	m_IsRunning = running;
}

void Game::SetScore(int score)
{
	m_Score = score;
}

int Game::GetScore() const
{
	return m_Score;
}
