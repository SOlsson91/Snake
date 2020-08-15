#pragma once
#include <vector>
#include "StateMachine.h"

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

class GameState : public State
{
private:
	const int MAP_WIDTH = 50;
	const int MAP_HEIGHT = 20;

	int m_Score;
	int m_TailLength;
	V2 m_PlayerPos;
	V2 m_FruitPos;
	std::vector<V2> m_Tail;
	Direction m_PlayerDirection;

	void SetRandomFruitLocation();
	bool DrawTail(int x, int y);
	void DrawScore();
	void DrawInfo();

public:
	GameState();
	~GameState();
	void OnEnter() override;
	void OnExit() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
};
