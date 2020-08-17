#pragma once

#include "Game.h"
#include "StateMachine.h"

class EndState : public State
{
public:
	EndState();
	void Update(float) override;
	void Render() override;
	void ProcessInput() override;
};
