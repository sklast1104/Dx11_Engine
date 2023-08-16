#pragma once
#include "StateMachine.h"
#include "StageManager.h"

namespace Jun::PlayerState {

	class PlayerStateMachine : public StateMachine
	{
	public:
		PlayerStateMachine();
		virtual ~PlayerStateMachine();

		virtual void Initialize() override;
		virtual void Start() override;

	public:

		StageManager* stageManager;
		GameObject* player;
		float delay;
	};
}



