#include <ncurses.h>
#include <vector>
#include <iostream>

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

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void GetInput();
	bool IsGameOver();
	void Sleep();
private:
	void SetRandomFruitLocation();

	const int MAP_WIDTH = 50;
	const int MAP_HEIGHT = 20;
	const unsigned int CONVERT_TO_SECONDS = 1'000'000;

	bool m_GameOver;
	int m_Score;
	int m_TailLength;
	double m_UpdatedPerSec = 0.1;
	V2 m_PlayerPos;
	V2 m_FruitPos;
	std::vector<V2> m_Tail;
	Direction m_PlayerDirection;
};
