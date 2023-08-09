#pragma once
#include "State.h"

namespace Jun {

	class DebugState : public State
	{
	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};
}



