#pragma once

#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>

class StateMachine;

class Game : public std::enable_shared_from_this<Game>
{
private:
	const double m_UpdatedPerSec = 0.1;
	const unsigned int CONVERT_TO_SECONDS = 1'000'000;
	WINDOW* m_Window;
	std::shared_ptr<StateMachine> m_StateMachine;
	bool m_IsRunning;
    unsigned int m_Score;
public:
	Game();
	~Game();
	void Run();
	void Sleep();
	std::shared_ptr<StateMachine> GetStateMachine() const;
	bool GetIsRunning() const;
	void SetIsRunning(bool running);
	void SetScore(int score);
	int GetScore() const;
};
