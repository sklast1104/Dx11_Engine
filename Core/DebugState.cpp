#include "DebugState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "Input.h"
#include <iostream>

using namespace Jun::math;

Vector3 backOffset = { -1.f, 0.f, 0.f };

int index = 0;

void Jun::DebugState::Enter()
{
	Transform* ownerTransform = owner->GetComponent<Transform>();

	ownerTransform->SetPosition(ownerTransform->GetPosition() + backOffset);


}

void Jun::DebugState::Update()
{
	if (Input::GetKeyDown(eKeyCode::SPACE)) {
		index += 1;

		std::cout << index << "\n";

		if (index > 6) {
			index = 0;
		}
	}

	if (index == 0) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
	}
	else if (index == 1) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Attack", true);
	}
	else if (index == 2) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Run", true);
	}
	else if (index == 3) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Damage", true);
	}
	else if (index == 4) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"JoyResult", true);
	}
	else if (index == 5) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"RunGS", true);
	}
	else if (index == 6) {
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"StandBy", true);
	}


}

void Jun::DebugState::Exit()
{
}
