#pragma once
#include "State.h"
#include "BattleManager.h"
#include "PlayerStateMachine.h"

namespace Jun::PlayerState {

	class IdleState : public State
	{
	public:

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private :
		class PlayerStateMachine* machine;
		class BattleManager* battleManager;
		float elapsedTime;
		float delay;
	};
}



