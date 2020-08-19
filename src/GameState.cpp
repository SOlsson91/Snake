#include "GameState.h"
#include "EndState.h"
#include <ncurses.h>

GameState::GameState()
{
	std::mt19937 generator(m_RandomDevice());
	const int startY = 0;
	const int startX = 0;
	m_Window = newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX);
	refresh();
}

void GameState::OnEnter()
{
	m_PlayerPos = {MAP_WIDTH / 2, MAP_HEIGHT / 2};
	m_GameOver = false;
	m_Score = 0;
	m_TailLength = 0;
	m_Tail.push_back(m_PlayerPos);
	SetRandomFruitLocation();
	SetRandomMoveDirection();
}

void GameState::OnExit()
{
	m_Tail.clear();
	Game::s_Score = m_Score;
}

void GameState::Update(float)
{
	if (m_GameOver)
		Game::stateMachine->PushState(std::make_unique<EndState>());

	V2 prevPos = m_PlayerPos;
	m_Tail[0] = m_PlayerPos;

	for (auto i = 0; i < m_TailLength; ++i)
	{
		V2 tempPos = m_Tail[i];
		m_Tail[i] = prevPos;
		prevPos = tempPos;
	}

	switch (m_PlayerDirection)
	{
	case UP:
		m_PlayerPos.y--;
		break;
	case DOWN:
		m_PlayerPos.y++;
		break;
	case LEFT:
		m_PlayerPos.x--;
		break;
	case RIGHT:
		m_PlayerPos.x++;
		break;
	default: case STOP:
		break;
	}

	for (auto i = 1; i < m_TailLength; ++i)
	{
		if (m_PlayerPos.x == m_Tail[i].x && m_PlayerPos.y == m_Tail[i].y)
		{
			m_PlayerDirection = Direction::STOP;
			m_GameOver = true;
		}
	}

	if (m_PlayerPos.x == 0 || m_PlayerPos.x > MAP_WIDTH - 2 || m_PlayerPos.y == 0 || m_PlayerPos.y > MAP_HEIGHT - 2)
	{
		m_PlayerDirection = Direction::STOP;
		m_GameOver = true;
	}

	if (m_FruitPos.x == m_PlayerPos.x && m_FruitPos.y == m_PlayerPos.y)
	{
		SetRandomFruitLocation();
		m_Score += 10;
		m_TailLength++;
		m_Tail.push_back({0,0});
	}
}

void GameState::Render()
{
	box(m_Window, 0, 0);
	for (auto y = 0; y < MAP_HEIGHT; y++)
	{
		for (auto x = 0; x < MAP_WIDTH; x++)
		{
			//move(y,x);
			if (x == 0 || x == (MAP_WIDTH - 1) || y == 0 || y == (MAP_HEIGHT - 1))
			{
				//printw("#");
			}
			else if ( y == m_PlayerPos.y && x == m_PlayerPos.x)
			{
				mvwprintw(m_Window, y, x, "O");
			}
			else if ( y == m_FruitPos.y && x == m_FruitPos.x)
			{
				mvwprintw(m_Window, y, x, "F");
			}
			else
			{
				if (!DrawTail(x, y))
					mvwprintw(m_Window, y, x, " ");
			}
		}
	}
	DrawScore();
	wrefresh(m_Window);
}

void GameState::ProcessInput()
{
	int key = getch();
	switch (key)
	{
	case KEY_UP : case 'w':
		if (m_PlayerDirection != Direction::DOWN)
			m_PlayerDirection = Direction::UP;
		break;
	case KEY_DOWN : case 's':
		if (m_PlayerDirection != Direction::UP)
			m_PlayerDirection = Direction::DOWN;
		break;
	case KEY_LEFT : case 'a':
		if (m_PlayerDirection != Direction::RIGHT)
			m_PlayerDirection = Direction::LEFT;
		break;
	case KEY_RIGHT : case 'd':
		if (m_PlayerDirection != Direction::LEFT)
			m_PlayerDirection = Direction::RIGHT;
		break;
	case 'q': case KEY_EXIT:
		m_PlayerDirection = Direction::STOP;
		Game::s_IsRunning = false;
		break;
	}
}


bool GameState::DrawTail(int x, int y)
{
	bool print = false;
	for (auto c = 0; c < m_TailLength; c++)
	{
		if (m_Tail[c].x == x && m_Tail[c].y == y)
		{
			mvwprintw(m_Window, m_Tail[c].y, m_Tail[c].x, "%c", 'o');
			print = true;
		}
	}
	return print;
}

void GameState::DrawScore()
{
	mvprintw(MAP_HEIGHT + 2, MAP_WIDTH / 2, "Score: %d", m_Score);
}

void GameState::SetRandomFruitLocation()
{
	m_FruitPos.x = m_RandomDevice() % (MAP_WIDTH - 3) + 2;
	m_FruitPos.y = m_RandomDevice() % (MAP_HEIGHT - 3) + 2;
}

void GameState::SetRandomMoveDirection()
{
	m_PlayerDirection = static_cast<Direction>(m_RandomDevice() % 4 + 1);
}

