#include "MonsterAttackState.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "MonsterStateMachine.h"

void Jun::MonsterAttackState::Enter()
{
	delay = 1.f;
	elapsedTime = 0.f;
	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Attack", false);
}

void Jun::MonsterAttackState::Update()
{
	elapsedTime += Time::DeltaTime();

	if (elapsedTime > delay) {
		MonsterStateMachine* machine = owner->GetComponent<MonsterStateMachine>();
		machine->SwitchState(machine->stateMap[L"IdleState"].get());
	}

}

void Jun::MonsterAttackState::Exit()
{
}
