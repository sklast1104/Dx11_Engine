#include "IdleState.h"
#include "GameObject.h"
#include "SkeletonMecanim.h"
#include "Input.h"
#include "PlayerStateMachine.h"

namespace Jun {


	void IdleState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
	}

	void IdleState::Update()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE)) {
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"AttackState"].get());
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"MoveState"].get());
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"MoveState"].get());
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"MoveState"].get());
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"MoveState"].get());
		}
		else {

		}
	}

	void IdleState::Exit()
	{
	}

}