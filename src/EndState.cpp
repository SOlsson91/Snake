#include "EndState.h"
#include "GameState.h"

#include <string.h>

EndState::EndState()
{
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);
	const int startY = maxY / 2 - MAP_HEIGHT / 2;
	const int startX = maxX / 2 - MAP_WIDTH / 2;
	m_Window = newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX);

	start_color();
	init_pair(Color::BACKGROUND, COLOR_WHITE, COLOR_BLACK);
	init_pair(Color::TEXT, COLOR_BLACK, COLOR_WHITE);
	wbkgd(m_Window, COLOR_PAIR(Color::BACKGROUND));
}

void EndState::Render()
{
	wclear(m_Window);
	box(m_Window, 0, 0);
	int i = 0;

	const char* score = "Score %i";
	wattron(m_Window, COLOR_PAIR(Color::BACKGROUND));
	mvwprintw(m_Window, MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(score) / 2, score, Game::s_Score);
	wattroff(m_Window, COLOR_PAIR(Color::BACKGROUND));
	i++;


	switch (m_Highlight)
	{
	case MENU_OPTIONS::START:
		wattron(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(replay) / 2, replay);
		wattroff(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
	break;
	case MENU_OPTIONS::EXIT:
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(replay) / 2, replay);
		wattron(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
		wattroff(m_Window, A_REVERSE);
	break;
	}
	wrefresh(m_Window);
}

void EndState::ProcessInput()
{
	switch (getch())
	{
	case 10: //ENTER
		if (m_Highlight == MENU_OPTIONS::START)
		{
			Game::stateMachine->PopState();
		}
		else if(m_Highlight == MENU_OPTIONS::EXIT)
		{
			Game::s_IsRunning = false;
		}
		break;
	case KEY_UP:
		m_Highlight = --m_Highlight < 0 ? 1 : m_Highlight;
		break;
	case KEY_DOWN:
		m_Highlight = ++m_Highlight > 1 ? 0 : m_Highlight;
		break;
	case 'q':
		Game::s_IsRunning = false;
		break;
	}
}
