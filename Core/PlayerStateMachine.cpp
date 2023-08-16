#include "PlayerStateMachine.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "StartState.h"
#include "DebugState.h"
#include "StandByState.h"
#include "NextState.h"
#include "Object.h"
#include "StageManager.h"

namespace Jun::PlayerState {

	using namespace Jun::object;

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

		stateMap[L"StartState"] = std::make_shared<StartState>();
		stateMap[L"StartState"].get()->owner = GetOwner();

		stateMap[L"DebugState"] = std::make_shared<DebugState>();
		stateMap[L"DebugState"].get()->owner = GetOwner();

		stateMap[L"StandByState"] = std::make_shared<StandByState>();
		stateMap[L"StandByState"].get()->owner = GetOwner();

		stateMap[L"NextState"] = std::make_shared<NextState>();
		stateMap[L"NextState"].get()->owner = GetOwner();

		currentState = stateMap[L"StartState"].get();
		currentState->Enter();

	}
	void PlayerStateMachine::Start()
	{
		stageManager = FindObjectOfType<StageManager>();
	}
}