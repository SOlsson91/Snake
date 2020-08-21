#pragma once
#include "StateMachine.h"
#include "Constants.h"
#include <vector>
#include <random>

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
	std::unique_ptr<WINDOW> m_GameWindow;
	std::unique_ptr<WINDOW> m_ScoreWindow;
	Game* m_Game;

	void SetRandomFruitLocation();
	void DrawTail(int x, int y);
	void DrawScore();

public:
	GameState(Game* game);
	~GameState();
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	void OnEnter() override;
	void OnExit() override;
};
