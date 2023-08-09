#include "StartState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "Input.h"
#include <iostream>
#include "MyTime.h"

using namespace Jun::math;

Vector3 backOffset = { -1.f, 0.f, 0.f };
Vector3 prevPos;
Vector3 dir = { 1.f, 0.f, 0.f };
float speed = 0.3f;

void Jun::StartState::Enter()
{
	ownerTransform =  owner->GetComponent<Transform>();

	ownerTransform->SetPosition(ownerTransform->GetPosition() + backOffset);

	prevPos = ownerTransform->GetPosition() + backOffset;

	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"RunGS", true);

	elapsedTime = 0.f;
}

void Jun::StartState::Update()
{
	elapsedTime += Time::DeltaTime();

	Vector3 movVec = dir * Time::DeltaTime() * speed;

	ownerTransform->SetPosition(ownerTransform->GetPosition() + movVec);

}

void Jun::StartState::Exit()
{
}
