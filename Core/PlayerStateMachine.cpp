#include "PlayerStateMachine.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"

namespace Jun {

	PlayerStateMachine::PlayerStateMachine()
	{
	}

	PlayerStateMachine::~PlayerStateMachine()
	{
	}

	void PlayerStateMachine::Initialize()
	{
		player = GetOwner();

		stateMap[L"IdleState"] = std::make_shared<IdleState>();
		stateMap[L"IdleState"].get()->owner = GetOwner();

		stateMap[L"MoveState"] = std::make_shared<MoveState>();
		stateMap[L"MoveState"].get()->owner = GetOwner();

		stateMap[L"AttackState"] = std::make_shared<AttackState>();
		stateMap[L"AttackState"].get()->owner = GetOwner();


		currentState = stateMap[L"IdleState"].get();
		currentState->Enter();

	}
}