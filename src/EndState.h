#pragma once

#include "Game.h"
#include "StateMachine.h"

class EndState : public State
{
private:
	const int MAP_WIDTH = 40;
	const int MAP_HEIGHT = 20;
public:
	EndState();
	void Render() override;
	void ProcessInput() override;
};
