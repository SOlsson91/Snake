#include "EndState.h"
#include "GameState.h"

EndState::EndState()
{
}

void EndState::Render()
{
	int i = 0;
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "Score: %i", Game::s_Score);
	i++;
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "To play the game again press 'ENTER'");
	mvprintw(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2, "To Quit press 'Q'");
}

void EndState::ProcessInput()
{
	int key = getch();
	switch (key)
	{
	case 10: //ENTER
		Game::stateMachine->PopState();
		break;
	case 'q': 
		Game::s_IsRunning = false;
		break;
	}
}
