#pragma once
#include "State.h"

namespace Jun {

	class MonsterAttackedState : public State
	{
	private :
		float delay;
		float elapsedTime;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};

}



