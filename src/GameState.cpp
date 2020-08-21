#include "GameState.h"
#include "EndState.h"
#include <ncurses.h>
#include <string.h>

GameState::GameState(Game* game)
	: m_Game(game)
{
	std::mt19937 generator(m_RandomDevice());
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);
	const int startX = maxX / 2 - MAP_WIDTH / 2;
	const int startY = maxY / 2 - MAP_HEIGHT / 2;
	m_GameWindow = static_cast<std::unique_ptr<WINDOW>>(newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX));
	m_ScoreWindow = static_cast<std::unique_ptr<WINDOW>>(newwin(SCORE_HEIGHT, MAP_WIDTH, startY + MAP_HEIGHT, startX));
}

GameState::~GameState()
{
	m_GameWindow.release();
	m_ScoreWindow.release();
}

void GameState::OnEnter()
{
	m_PlayerPos = {MAP_WIDTH / 2, MAP_HEIGHT / 2};
	m_GameOver = false;
	m_Score = 0;
	m_TailLength = 0;
	SetRandomFruitLocation();
	m_PlayerDirection = static_cast<Direction>(m_RandomDevice() % 4 + 1);
	clear();
}

void GameState::OnExit()
{
	m_Tail.clear();
	m_Game->SetScore(m_Score);
}

void GameState::Update(float)
{
	if (m_GameOver)
	{
		m_Game->GetStateMachine()->PushState(std::make_unique<EndState>(m_Game));
	}

	V2 prevPos = m_PlayerPos;
	for (auto i = 0; i < m_TailLength; ++i)
	{
		V2 tempPos = m_Tail[i];
		m_Tail[i] = prevPos;
		prevPos = tempPos;
	}

	switch (m_PlayerDirection)
	{
	case Direction::Up:
		m_PlayerPos.y--;
		break;
	case Direction::Down:
		m_PlayerPos.y++;
		break;
	case Direction::Left:
		m_PlayerPos.x--;
		break;
	case Direction::Right:
		m_PlayerPos.x++;
		break;
	default: case Direction::Stop:
		break;
	}

	for (auto i = 0; i < m_TailLength; ++i)
	{
		if (m_PlayerPos.x == m_Tail[i].x && m_PlayerPos.y == m_Tail[i].y)
		{
			m_PlayerDirection = Direction::Stop;
			m_GameOver = true;
		}
	}

	if (m_PlayerPos.x == 0 || m_PlayerPos.x > MAP_WIDTH - 2 || m_PlayerPos.y == 0 || m_PlayerPos.y > MAP_HEIGHT - 2)
	{
		m_PlayerDirection = Direction::Stop;
		m_GameOver = true;
	}

	if (m_FruitPos.x == m_PlayerPos.x && m_FruitPos.y == m_PlayerPos.y)
	{
		m_Tail.push_back(m_FruitPos);
		m_TailLength++;
		m_Score += 10;
		SetRandomFruitLocation();
	}
}

void GameState::Render()
{
	wclear(m_GameWindow.get());
	wclear(m_ScoreWindow.get());

	box(m_GameWindow.get(), 0, 0);
	for (auto y = 0; y < MAP_HEIGHT; y++)
	{
		for (auto x = 0; x < MAP_WIDTH; x++)
		{
			if ( y == m_PlayerPos.y && x == m_PlayerPos.x)
			{
				wattron(m_GameWindow.get(), COLOR_PAIR(Colors::SnakeColor));
				mvwaddch(m_GameWindow.get(), y, x, 'O');
				wattroff(m_GameWindow.get(), COLOR_PAIR(Colors::SnakeColor));
			}
			else if ( y == m_FruitPos.y && x == m_FruitPos.x)
			{
				wattron(m_GameWindow.get(), COLOR_PAIR(Colors::FruitColor));
				mvwaddch(m_GameWindow.get(), y, x, 'F');
				wattroff(m_GameWindow.get(), COLOR_PAIR(Colors::FruitColor));
			}
			DrawTail(x, y);
		}
	}
	box(m_ScoreWindow.get(), 0, 0);
	DrawScore();

	wrefresh(m_ScoreWindow.get());
	wrefresh(m_GameWindow.get());
}

void GameState::ProcessInput()
{
	switch (getch())
	{
	case KEY_UP : case 'w':
		if (m_PlayerDirection != Direction::Down)
			m_PlayerDirection = Direction::Up;
		break;
	case KEY_DOWN : case 's':
		if (m_PlayerDirection != Direction::Up)
			m_PlayerDirection = Direction::Down;
		break;
	case KEY_LEFT : case 'a':
		if (m_PlayerDirection != Direction::Right)
			m_PlayerDirection = Direction::Left;
		break;
	case KEY_RIGHT : case 'd':
		if (m_PlayerDirection != Direction::Left)
			m_PlayerDirection = Direction::Right;
		break;
	case 'q': case KEY_EXIT:
		m_PlayerDirection = Direction::Stop;
		m_Game->SetIsRunning(false);
		break;
	}
}


void GameState::DrawTail(int x, int y)
{
	for (auto c = 0; c < m_TailLength; c++)
	{
		if (m_Tail[c].x == x && m_Tail[c].y == y)
		{
			wattron(m_GameWindow.get(), COLOR_PAIR(Colors::SnakeColor));
			mvwaddch(m_GameWindow.get(), m_Tail[c].y, m_Tail[c].x, 'o');
			wattroff(m_GameWindow.get(), COLOR_PAIR(Colors::SnakeColor));
		}
	}
}
void GameState::DrawScore()
{
	const char* score = "Score: %d";

	wattron(m_GameWindow.get(), COLOR_PAIR(Colors::TextColor));
	mvwprintw(m_ScoreWindow.get(), SCORE_HEIGHT / 2, MAP_WIDTH / 2 - strlen(score) / 2, score, m_Score);
	wattroff(m_GameWindow.get(), COLOR_PAIR(Colors::TextColor));
}

void GameState::SetRandomFruitLocation()
{
	m_FruitPos.x = m_RandomDevice() % (MAP_WIDTH - 3) + 2;
	m_FruitPos.y = m_RandomDevice() % (MAP_HEIGHT - 3) + 2;
}
