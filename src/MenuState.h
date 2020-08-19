#pragma once

#include "./StateMachine.h"

enum MENU_OPTIONS
{
	START = 0,
	EXIT = 1
};

class MenuState : public State
{
private:
	const int MAP_WIDTH = 40;
	const int MAP_HEIGHT = 20;
	const char * header = "#----- Snake -----#";
	const char * subheader = "By: Sebastian Olsson";
	const char * start = "Start";
	const char * quit = "Quit";

	int m_Highlight = 0;
	WINDOW* m_Window;
public:
	MenuState();
	void Render() override;
	void ProcessInput() override;
};
