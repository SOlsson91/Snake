#pragma once
#include "StateMachine.h"
#include <vector>
#include <random>

struct V2
{
	int x;
	int y;
};

enum Direction
{
	STOP = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

enum Color
{
	BACKGROUND = 1,
	SNAKE = 2,
	FRUIT = 3,
	TEXT = 4
};

class GameState : public State
{
private:
	const int SCORE_HEIGHT = 4;
	const int MAP_WIDTH = 50;
	const int MAP_HEIGHT = 20;
	bool m_GameOver;
	int m_Score;
	int m_TailLength;
	V2 m_PlayerPos;
	V2 m_FruitPos;
	std::vector<V2> m_Tail;
	Direction m_PlayerDirection;
	std::random_device m_RandomDevice;
	WINDOW* m_GameWindow;
	WINDOW* m_ScoreWindow;

	void SetRandomFruitLocation();
	bool DrawTail(int x, int y);
	void DrawScore();
	void DrawInfo();
	void SetRandomMoveDirection();

public:
	GameState();
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	void OnEnter() override;
	void OnExit() override;
};
