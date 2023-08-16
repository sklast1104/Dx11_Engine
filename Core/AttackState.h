#pragma once
#include "State.h"
#include "BattleManager.h"

namespace Jun::PlayerState {

	class AttackState : public State
	{
	private :
		float delay;
		float elapsedTime;
		BattleManager* manager;

		bool canAttack;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};
}



