#pragma once

enum Colors
{
	BackgroundColor = 1,
	SnakeColor = 2,
	FruitColor = 3,
	TextColor = 4
};

struct V2
{
	int x;
	int y;
};

enum Direction
{
	Stop = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4
};

enum EndMenuOptions
{
	Restart = 0,
	Quit = 1
};

enum MenuOptions
{
	Start = 0,
	Exit = 1
};
