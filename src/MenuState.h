#pragma once

#include "./StateMachine.h"

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
	std::unique_ptr<WINDOW> m_Window;

	enum MENU_OPTIONS
	{
		START = 0,
		EXIT = 1
	};
	Game* m_Game;

public:
	MenuState(Game* game);
	~MenuState();
	void Render() override;
	void ProcessInput() override;
};
