#pragma once
#include "State.h"

namespace Jun {

	class MonsterDieState : public State
	{
	private :

		float elapsedTime;
		float delay;
		bool flag;
	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};

}



