#include "AttackState.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "PlayerStateMachine.h"
#include "MonsterStateMachine.h"
#include "Health.h"
#include "BattleManager.h"
#include "HpValController.h"

#include <iostream>

namespace Jun::PlayerState {

	void AttackState::Enter()
	{
		delay = 1.f;
		elapsedTime = 0.f;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Attack", false);
		manager = owner->GetComponent<BattleManager>();

		canAttack = true;
	}

	void AttackState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > 0.3f && canAttack) {

			canAttack = false;

			GameObject* monster = manager->FindTarget();

			if (monster != nullptr) {
				MonsterStateMachine* monMachine = monster->GetComponent<MonsterStateMachine>();

				Health* monHealth = monster->GetComponent<Health>();
				HpValController* con = monster->GetComponentInChild<HpValController>();

				monHealth->DealDamage(1.f);
				con->SetPercent(0.1f);

				monMachine->SwitchState(monMachine->stateMap[L"AttackedState"].get());
			}
		}

		if (elapsedTime > delay) {
			

			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"IdleState"].get());
		}
	}

	void AttackState::Exit()
	{
	}

}