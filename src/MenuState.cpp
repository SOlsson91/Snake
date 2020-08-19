#include "MenuState.h"
#include "GameState.h"

#include <ncurses.h>
#include <string.h>

MenuState::MenuState()
	: m_Highlight(0)
{
	int maxY, maxX;
	getmaxyx(stdscr, maxY, maxX);
	const int startY = maxY / 2 - MAP_HEIGHT / 2;
	const int startX = maxX / 2 - MAP_WIDTH / 2;
	m_Window = newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX);

	start_color();
	init_pair(Color::BACKGROUND, COLOR_WHITE, COLOR_BLACK);
	init_pair(Color::TEXT, COLOR_BLACK, COLOR_WHITE);
	wbkgd(m_Window, COLOR_PAIR(Color::BACKGROUND));
}

void MenuState::Render()
{
	wclear(m_Window);
	box(m_Window, 0, 0);
	int i = 0;

	wattron(m_Window, COLOR_PAIR(Color::BACKGROUND));
	mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(header) / 2, header);
	mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(subheader) / 2, subheader);
	wattroff(m_Window, COLOR_PAIR(Color::BACKGROUND));
	i++;

	// NOTE: Wow... This was a ugly hack... To tired to work out a propper solution right now. Will get back to this
	// TODO
	switch (m_Highlight)
	{
	case MENU_OPTIONS::START:
		wattron(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(start) / 2, start);
		wattroff(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
	break;
	case MENU_OPTIONS::EXIT:
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(start) / 2, start);
		wattron(m_Window, A_REVERSE);
		mvwprintw(m_Window, MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
		wattroff(m_Window, A_REVERSE);
	break;
	}
	wrefresh(m_Window);
}

void MenuState::ProcessInput()
{
	switch (getch())
	{
	case 10: //ENTER
		if (m_Highlight == MENU_OPTIONS::START)
		{
			Game::stateMachine->PopState();
			Game::stateMachine->PushState(std::make_unique<GameState>());
		}
		else if (m_Highlight == MENU_OPTIONS::EXIT)
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
