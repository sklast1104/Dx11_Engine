#include "MonsterAttackedState.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "MonsterStateMachine.h"

#include <iostream>

namespace Jun {

	void MonsterAttackedState::Enter()
	{
		delay = 0.6f;
		elapsedTime = 0.f;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Damage", false);
	}

	void MonsterAttackedState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > delay) {
			MonsterStateMachine* machine = owner->GetComponent<MonsterStateMachine>();
			machine->SwitchState(machine->stateMap[L"IdleState"].get());
		}
	}

	void MonsterAttackedState::Exit()
	{

	}

}