#pragma once
#include "State.h"

namespace Jun {
	class BattleManager;
}

namespace Jun::PlayerState {

	class AttackState : public State
	{
	private :
		float delay;
		float elapsedTime;
		Jun::BattleManager* manager;

		bool canAttack;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};
}



