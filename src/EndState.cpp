#include "EndState.h"

#include <string.h>
#include <menu.h>

EndState::EndState(Game* game)
	: m_Game(game)
{
	int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);
	const int startY = maxY / 2 - MAP_HEIGHT / 2;
	const int startX = maxX / 2 - MAP_WIDTH / 2;
	m_Window = static_cast<std::unique_ptr<WINDOW>>(newwin(MAP_HEIGHT, MAP_WIDTH, startY, startX));
}

EndState::~EndState()
{
	m_Window.release();
}

void EndState::Render()
{
	wclear(m_Window.get());
	box(m_Window.get(), 0, 0);
	int i = 0;

	const char* score = "Score %i";
	wattron(m_Window.get(), COLOR_PAIR(Colors::BackgroundColor));
	mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(score) / 2, score, m_Game->GetScore());
	wattroff(m_Window.get(), COLOR_PAIR(Colors::BackgroundColor));
	i++;

	wattron(m_Window.get(), m_Highlight == static_cast<int>(EndMenuOptions::Start) ? A_REVERSE : 0);
	mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(replay) / 2, replay);
	wattroff(m_Window.get(), m_Highlight == static_cast<int>(EndMenuOptions::Start) ? A_REVERSE : 0);

	wattron(m_Window.get(), m_Highlight == static_cast<int>(EndMenuOptions::Quit) ? A_REVERSE : 0);
	mvwprintw(m_Window.get(), MAP_HEIGHT / 2 - 2 + i++, MAP_WIDTH / 2 - strlen(quit) / 2, quit);
	wattroff(m_Window.get(), m_Highlight == static_cast<int>(EndMenuOptions::Quit) ? A_REVERSE : 0);

	wrefresh(m_Window.get());
}

void EndState::ProcessInput()
{
	switch (getch())
	{
	case 10: //ENTER
		if (m_Highlight == static_cast<int>(EndMenuOptions::Start))
		{
			m_Game->GetStateMachine()->PopState();
		}
		else if(m_Highlight == static_cast<int>(EndMenuOptions::Quit))
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
