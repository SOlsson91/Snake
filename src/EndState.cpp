#include "EndState.h"
#include "GameState.h"

EndState::EndState()
{
}

void EndState::Update(float)
{
}

void EndState::Render()
{
	clear();
	int i = 0;
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("Score: %i", Game::s_Score);
	i++;
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("To play the game again press 'ENTER'");
	move(MAP_HEIGHT / 2 + i++, MAP_WIDTH / 2);
	printw("To Quit press 'Q'");
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
