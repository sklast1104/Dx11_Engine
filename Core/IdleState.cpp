#include "IdleState.h"
#include "GameObject.h"
#include "SkeletonMecanim.h"
#include "Input.h"
#include "PlayerStateMachine.h"
#include "Object.h"
#include "MonsterStateMachine.h"
#include "BattleManager.h"
#include "MyTime.h"

#include <iostream>

namespace Jun::PlayerState {

	using namespace Jun::object;

	void IdleState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);

		Scene* scene = SceneManager::GetActiveScene();

		battleManager = owner->GetComponent<BattleManager>();

		elapsedTime = 0.f;
		delay = 1.f;

		machine = owner->GetComponent<PlayerStateMachine>();
	}

	void IdleState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (battleManager->IsMove()) {

			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"MoveState"].get());

		}
		else {

			if (elapsedTime > delay) {
				PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
				machine->SwitchState(machine->stateMap[L"AttackState"].get());
			}
		}
	}

	void IdleState::Exit()
	{
	}

}