#include "StandByState.h"
#include "MyTime.h"
#include "SkeletonMecanim.h"
#include "PlayerStateMachine.h"

#include <iostream>
#include <random>

namespace Jun::PlayerState {

	void StandByState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"StandBy", false);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.0f, 0.5f);
		float randomValue = dist(gen);

		delay = 2.f;
		delay += randomValue;

		elapsedTime = 0.f;
	}

	void StandByState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > delay) {

			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"IdleState"].get());

		}
	}

	void StandByState::Exit()
	{
	}

}