#pragma once
#include "State.h"

namespace Jun {

	class MonsterIdleState : public State
	{
	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private :
		class MonsterBattleManager* manager;
		float elapsedTime;
		float delay;
	};
}


