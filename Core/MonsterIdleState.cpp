#include "MonsterIdleState.h"
#include "SkeletonMecanim.h"
#include "MonsterBattleManager.h"
#include "Object.h"
#include "MyTime.h"
#include "MonsterStateMachine.h"

namespace Jun {

	using namespace Jun::object;

	void MonsterIdleState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
		manager = FindObjectOfType<MonsterBattleManager>();

		elapsedTime = 0.f;
		delay = 1.f;
	}

	void MonsterIdleState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > delay) {

			MonsterStateMachine* machine = owner->GetComponent<MonsterStateMachine>();
			machine->SwitchState(machine->stateMap[L"AttackState"].get());

		}
	}

	void MonsterIdleState::Exit()
	{
	}

}