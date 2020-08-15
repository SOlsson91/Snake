#include <ncurses.h>
#include "GameState.h"

GameState::GameState()
	: m_Score(0), m_TailLength(0), m_PlayerPos({(MAP_WIDTH / 2), (MAP_HEIGHT / 2)}),
	m_PlayerDirection(Direction::UP)
{
	m_Tail.push_back(m_PlayerPos);
	srand(time(0));
	SetRandomFruitLocation();
}

GameState::~GameState()
{
}

void GameState::OnEnter()
{
}

void GameState::OnExit()
{
}

void GameState::Update(float dt)
{
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

			Game::s_IsRunning = false;
		}
	}

	if (m_PlayerPos.x == 0 || m_PlayerPos.x > MAP_WIDTH - 2 || m_PlayerPos.y == 0 || m_PlayerPos.y > MAP_HEIGHT - 2)
	{
		m_PlayerDirection = Direction::STOP;
		Game::s_IsRunning = false;
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
	clear();
	for (auto y = 0; y < MAP_HEIGHT; y++)
	{
		for (auto x = 0; x < MAP_WIDTH; x++)
		{
			move(y,x);
			if (x == 0 || x == (MAP_WIDTH - 1) || y == 0 || y == (MAP_HEIGHT - 1))
			{
				printw("#");
			}
			else if ( y == m_PlayerPos.y && x == m_PlayerPos.x)
			{
				printw("O");
			}
			else if ( y == m_FruitPos.y && x == m_FruitPos.x)
			{
				printw("F");
			}
			else
			{
				if (!DrawTail(x, y))
					printw(" ");
			}
		}
	}
	DrawInfo();
	DrawScore();
}

void GameState::ProcessInput()
{
	move(m_PlayerPos.y, m_PlayerPos.x);
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
			move(m_Tail[c].y, m_Tail[c].x);
			printw("o");
			print = true;
		}
	}
	return print;
}

void GameState::DrawScore()
{
	move(MAP_HEIGHT / 2, MAP_WIDTH + 1);
	printw("Score: %d", m_Score);
}

void GameState::DrawInfo()
{
	int i = 0;
	move(i++, MAP_WIDTH + 1);
	printw("Movement");
	move(i++, MAP_WIDTH + 1);
	printw("Left = 'A' / Left-arrow");
	move(i++, MAP_WIDTH + 1);
	printw("Right = 'D' / Right-arrow");
	move(i++, MAP_WIDTH + 1);
	printw("Up = 'W' / Up-arrow");
	move(i++, MAP_WIDTH + 1);
	printw("Down = 'S' / Down-arrow");
	move(i++, MAP_WIDTH + 1);
	printw("Quit = 'Q'");
}

void GameState::SetRandomFruitLocation()
{
	m_FruitPos.x = rand() % (MAP_WIDTH - 3) + 2;
	m_FruitPos.y = rand() % (MAP_HEIGHT - 3) + 2;
}

