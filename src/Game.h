#pragma once

#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>

class StateMachine;

class Game 
{
private:
	std::shared_ptr<StateMachine> m_StateMachine;
	bool m_IsRunning;
    unsigned int m_Score;
public:
	Game();
	~Game();
	void Run();
	std::shared_ptr<StateMachine> GetStateMachine() const;
	bool GetIsRunning() const;
	void SetIsRunning(bool running);
	void SetScore(int score);
	int GetScore() const;
};
