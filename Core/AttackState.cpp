#include "AttackState.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "PlayerStateMachine.h"

namespace Jun {

	float delay = 2.6f;
	float elapsedTime = 0.f;

	void AttackState::Enter()
	{
		elapsedTime = 0.f;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Attack", false);
	}

	void AttackState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > delay) {
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"IdleState"].get());
		}
	}

	void AttackState::Exit()
	{
	}

}