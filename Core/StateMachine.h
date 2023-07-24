#pragma once
#include "Script.h"

namespace Jun {

	class State;

	class StateMachine : public Script
	{
	public:
		StateMachine();
		virtual ~StateMachine();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SwitchState(State* newState);

	public:
		State* currentState;

	};

}



