#include "MoveState.h"
#include "Input.h"
#include "PlayerStateMachine.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"

void Jun::MoveState::Enter()
{
	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Walk", true);
}

void Jun::MoveState::Update()
{
	Transform* tr = owner->GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();

	float speed = 2.f;

	if (Input::GetKeyDown(eKeyCode::SPACE)) {
		PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
		machine->SwitchState(machine->stateMap[L"AttackState"].get());
	}

	if (Input::GetKey(eKeyCode::LEFT))
	{
		pos.x -= speed * Time::DeltaTime();
		tr->SetPosition(pos);
	}
	else if (Input::GetKey(eKeyCode::RIGHT))
	{
		pos.x += speed * Time::DeltaTime();
		tr->SetPosition(pos);
	}
	else if (Input::GetKey(eKeyCode::DOWN))
	{
		pos.y -= speed * Time::DeltaTime();
		tr->SetPosition(pos);
	}
	else if (Input::GetKey(eKeyCode::UP))
	{
		pos.y += speed * Time::DeltaTime();
		tr->SetPosition(pos);
	}
	else {
		PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
		machine->SwitchState(machine->stateMap[L"IdleState"].get());
	}
}

void Jun::MoveState::Exit()
{
}
