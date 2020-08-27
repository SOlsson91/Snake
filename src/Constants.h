#pragma once

enum class Colors
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

enum class Direction
{
	Stop = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4
};

enum class EndMenuOptions
{
	Start = 0,
	Quit = 1
};

enum class MenuOptions
{
	Start = 0,
	Quit = 1
};
