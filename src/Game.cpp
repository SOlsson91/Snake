#include <unistd.h>
#include "./Game.h"
#include "./MenuState.h"

std::unique_ptr<StateMachine> Game::stateMachine = std::make_unique<StateMachine>();

Game::Game()
	: m_GameOver(false), m_Score(0), m_TailLength(0), m_PlayerPos({(MAP_WIDTH / 2), (MAP_HEIGHT / 2)}),
	m_PlayerDirection(Direction::UP)
{
	m_Tail.push_back(m_PlayerPos);
	srand(time(0));
	SetRandomFruitLocation();
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

void Game::Sleep()
{
	refresh();
	usleep(m_UpdatedPerSec * CONVERT_TO_SECONDS);
}

void Game::SetRandomFruitLocation()
{
	m_FruitPos.x = rand() % (MAP_WIDTH - 3) + 2;
	m_FruitPos.y = rand() % (MAP_HEIGHT - 3) + 2;
}

bool Game::IsGameOver()
{
	return m_GameOver;
}

void Game::Draw()
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

bool Game::DrawTail(int x, int y)
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

void Game::DrawScore()
{
	move(MAP_HEIGHT / 2, MAP_WIDTH + 1);
	printw("Score: %d", m_Score);
}

void Game::DrawInfo()
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

void Game::GetInput()
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
	case 'q':
		m_PlayerDirection = Direction::STOP;
		m_GameOver = true;
		break;
	}
}

void Game::Update()
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
