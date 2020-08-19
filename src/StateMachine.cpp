#include "./StateMachine.h"

StateMachine::StateMachine()
{}

void StateMachine::PushState(std::unique_ptr<State> state)
{
	if (!this->states.empty())
	{
		this->states.top()->OnExit();
	}
	this->states.push(std::move(state));
	this->states.top()->OnEnter();
}

void StateMachine::PopState()
{
	this->states.top()->OnExit();
	this->states.pop();
	if (!this->states.empty())
	{
		this->states.top()->OnEnter();
	}
}

void StateMachine::Update(float dt)
{
	if (!this->states.empty())
	{
		this->states.top()->Update(dt);
	}
}

void StateMachine::Render()
{
	if (!this->states.empty())
	{
		this->states.top()->Render();
	}
}

void StateMachine::ProcessInput()
{
	if (!this->states.empty())
	{
		this->states.top()->ProcessInput();
	}
}

const State& StateMachine::GetActiveState()
{
	return *this->states.top();
}

int StateMachine::GetNumStates() const
{
	return this->states.size();
}

void StateMachine::SetWindow(WINDOW& window)
{
	this->m_Window = &window;
}
WINDOW& StateMachine::GetWindow() const
{
	return *this->m_Window;
}
