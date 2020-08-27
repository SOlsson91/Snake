#include "MenuState.h"
#include "GameState.h"

#include <ncurses.h>
#include <string.h>

MenuState::MenuState(Game* game)
	: m_Highlight(0), m_Game(game)
{
	int maxY, maxX;
	getmaxyx(stdscr, maxY, maxX);
	const int startY = maxY / 2 - MAP_HEIGHT / 2;
	const int startX = maxX / 2 - MAP_WIDTH / 2;
	m_Window = static_cast<std::unique_ptr<WINDOW>>(newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX));
}

MenuState::~MenuState()
{
	m_Window.release();
}

void MenuState::Render()
{
	wclear(m_Window.get());
	box(m_Window.get(), 0, 0);
	int i = 0;

	wattron(m_Window.get(), COLOR_PAIR(Colors::BackgroundColor));
	mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(header) / 2, header);
	mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(subheader) / 2, subheader);
	wattroff(m_Window.get(), COLOR_PAIR(Colors::BackgroundColor));
	i++;

	// NOTE: Wow... This was a ugly hack... To tired to work out a propper solution right now. Will get back to this
	// TODO
	switch (m_Highlight)
	{
	case static_cast<int>(MenuOptions::Start):
		wattron(m_Window.get(), A_REVERSE);
		mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(start) / 2, start);
		wattroff(m_Window.get(), A_REVERSE);
		mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
	break;
	case static_cast<int>(MenuOptions::Quit):
		mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(start) / 2, start);
		wattron(m_Window.get(), A_REVERSE);
		mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 4 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
		wattroff(m_Window.get(), A_REVERSE);
	break;
	}
	wrefresh(m_Window.get());
}

void MenuState::ProcessInput()
{
	switch (getch())
	{
	case 10: //ENTER
		if (m_Highlight == static_cast<int>(MenuOptions::Start))
		{
			m_Game->GetStateMachine()->PopState();
			m_Game->GetStateMachine()->PushState(std::make_unique<GameState>(m_Game));
		}
		else if (m_Highlight == static_cast<int>(MenuOptions::Quit))
		{
			m_Game->SetIsRunning(false);
		}
		break;
	case KEY_UP:
		m_Highlight = --m_Highlight < 0 ? 1 : m_Highlight;
		break;
	case KEY_DOWN:
		m_Highlight = ++m_Highlight > 1 ? 0 : m_Highlight;
		break;
	case 'q':
		m_Game->SetIsRunning(false);
		break;
	}
}
