#pragma once
#include "State.h"
#include "BattleManager.h"

namespace Jun::PlayerState {

	class MoveState : public State
	{
	private :
		class Transform* transform;
		Vector3 dir = { 1.f, 0.f, 0.f };
		BattleManager* battleManager;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

}



