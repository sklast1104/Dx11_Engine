#include "StartState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "Input.h"
#include <iostream>
#include "MyTime.h"
#include "MyMath.h"
#include "PlayerStateMachine.h"
#include "TransContainer.h"
#include "StageManager.h"
#include "Object.h"

#include <iostream>

using namespace Jun::math;

Vector3 backOffset = { -2.f, 0.f, 0.f };
Vector3 dir = { 1.f, 0.f, 0.f };
float speed = 1.f;

void Jun::PlayerState::StartState::Enter()
{
	using namespace Jun::object;

	ownerTransform = owner->GetComponent<Transform>();

	destPos = owner->GetComponent<TransContainer>()->Pos;

	ownerTransform->SetPosition(destPos + backOffset);

	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"RunGS", true);

	elapsedTime = 0.f;
}

void Jun::PlayerState::StartState::Update()
{
	elapsedTime += Time::DeltaTime();

	float dist = Vector3::Distance(destPos, ownerTransform->GetPosition());

	if (dist < 0.1f) {
		PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
		machine->SwitchState(machine->stateMap[L"StandByState"].get());
	}

	Vector3 movVec = dir * Time::DeltaTime() * speed;
	Vector3 position = ownerTransform->GetPosition();

	ownerTransform->SetPosition(ownerTransform->GetPosition() + movVec);

}

void Jun::PlayerState::StartState::Exit()
{
	owner->GetComponent<PlayerStateMachine>()->stageManager->ResetStageConfig();
}
