#pragma once

#include "./StateMachine.h"

enum MENU_OPTIONS
{
	START = 0,
	EXIT = 1
};

class MenuState : public State
{
public:
	MenuState();
	~MenuState();
	void OnEnter() override;
	void OnExit() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
};
