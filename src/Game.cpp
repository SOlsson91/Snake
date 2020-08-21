#include "Game.h"
#include "MenuState.h"
#include "GameState.h"
#include <chrono>
#include <thread>

Game::Game()
	: m_StateMachine(std::make_shared<StateMachine>()), m_IsRunning(true), m_Score(0)
{
	m_StateMachine->PushState(std::make_unique<MenuState>(this));
}

void Game::InitNcurses() const
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();

	start_color();
	init_pair(Colors::BackgroundColor, COLOR_WHITE, COLOR_BLACK);
	init_pair(Colors::SnakeColor, COLOR_GREEN, COLOR_GREEN);
	init_pair(Colors::FruitColor, COLOR_RED, COLOR_RED);
	init_pair(Colors::TextColor, COLOR_WHITE, COLOR_WHITE);
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

		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
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
