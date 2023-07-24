#include "StateMachine.h"
#include "State.h"

namespace Jun {
	StateMachine::StateMachine()
		: currentState{nullptr}
	{
	}
	StateMachine::~StateMachine()
	{
	}
	void StateMachine::Initialize()
	{
	}
	void StateMachine::Update()
	{
		if (currentState != nullptr) {
			currentState->Update();
		}
	}
	void StateMachine::LateUpdate()
	{
		if (currentState != nullptr) {
			currentState->LateUpdate();
		}
	}
	void StateMachine::Render()
	{
	}

	void StateMachine::SwitchState(State* newState)
	{
		if (currentState != nullptr)
		{
			currentState->Exit();
		}
		currentState = newState;

		if (currentState != nullptr) {
			currentState->Enter();
		}

	}
}