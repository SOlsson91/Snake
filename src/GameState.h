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
	bool m_GameOver;
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
	void SetRandomMoveDirection();

public:
	GameState();
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	void OnEnter() override;
	void OnExit() override;
};
