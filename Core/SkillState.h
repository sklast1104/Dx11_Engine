#pragma once
#include "State.h"

namespace Jun::PlayerState {

	class SkillState : public State
	{
	private :

		float elapsed;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};


}


