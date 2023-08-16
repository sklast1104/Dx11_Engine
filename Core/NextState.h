#pragma once
#include "State.h"
#include "Fader.h"
#include "StageManager.h"

namespace Jun::PlayerState {

	class NextState : public State
	{

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private :
		float delay;
		float nextDelay;
		float elapsedTime;
		Vector3 dir = { 1.f, 0.f, 0.f };

		bool flag = true;
		bool faderFlag = true;

		Fader* fader;
		StageManager* stageManager;
	};
}



