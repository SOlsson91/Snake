#include "./Game.h"

int main()
{
	Game game;
	while (!game.IsGameOver())
	{
		game.Draw();
		game.GetInput();
		game.Update();
		game.Sleep();
	}
}
