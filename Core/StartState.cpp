#include "StartState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"

using namespace Jun::math;

Vector3 backOffset = { -1.f, 0.f, 0.f };

void Jun::StartState::Enter()
{
	Transform* ownerTransform =  owner->GetComponent<Transform>();

	ownerTransform->SetPosition(ownerTransform->GetPosition() + backOffset);

	owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
}

void Jun::StartState::Update()
{
}

void Jun::StartState::Exit()
{
}
