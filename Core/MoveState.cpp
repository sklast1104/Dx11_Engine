#include "MoveState.h"
#include "Input.h"
#include "PlayerStateMachine.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "Transform.h"

void Jun::PlayerState::MoveState::Enter()
{
	transform = owner->GetComponent<Transform>();

	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Run", true);
	battleManager = owner->GetComponent<BattleManager>();
}

void Jun::PlayerState::MoveState::Update()
{
	if (!battleManager->IsMove()) {
		PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
		machine->SwitchState(machine->stateMap[L"IdleState"].get());
	}

	Transform* tr = owner->GetComponent<Transform>();

	float speed = 0.3f;

	Vector3 movVec = dir * Time::DeltaTime() * speed;

	tr->SetPosition(tr->GetPosition() + movVec);
}

void Jun::PlayerState::MoveState::Exit()
{
}
