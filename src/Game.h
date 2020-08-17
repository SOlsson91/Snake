#pragma once

#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>

class StateMachine;

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 20;

class Game
{
private:
	const double m_UpdatedPerSec = 0.1;
	const unsigned int CONVERT_TO_SECONDS = 1'000'000;
public:
	Game();
	~Game();
	void Run();
	void Sleep();

	static std::unique_ptr<StateMachine> stateMachine;
	static bool s_IsRunning;
    static unsigned int s_Score;
};
