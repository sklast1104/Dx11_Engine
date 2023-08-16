#pragma once
#include "State.h"

namespace Jun::PlayerState {

	class DebugState : public State
	{
	private :
		int index;
		bool animFlag;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}



