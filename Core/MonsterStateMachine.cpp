#include "MonsterStateMachine.h"
#include "MonsterStartState.h"
#include "MonsterIdleState.h"
#include "MonsterAttackState.h"
#include "MonsterAttackedState.h"

Jun::MonsterStateMachine::MonsterStateMachine()
{
}

Jun::MonsterStateMachine::~MonsterStateMachine()
{
}

void Jun::MonsterStateMachine::Initialize()
{
	monster = GetOwner();

	stateMap[L"StartState"] = std::make_shared<MonsterStartState>();
	stateMap[L"StartState"].get()->owner = GetOwner();

	stateMap[L"IdleState"] = std::make_shared<MonsterIdleState>();
	stateMap[L"IdleState"].get()->owner = GetOwner();

	stateMap[L"AttackState"] = std::make_shared<MonsterAttackState>();
	stateMap[L"AttackState"].get()->owner = GetOwner();

	stateMap[L"AttackedState"] = std::make_shared<MonsterAttackedState>();
	stateMap[L"AttackedState"].get()->owner = GetOwner();

	currentState = stateMap[L"StartState"].get();
	currentState->Enter();
}
