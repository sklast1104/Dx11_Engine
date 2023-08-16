#include "DebugState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "Input.h"
#include <iostream>

using namespace Jun::math;

void Jun::PlayerState::DebugState::Enter()
{
	index = 0;
	animFlag = true;
}

void Jun::PlayerState::DebugState::Update()
{
	if (Input::GetKeyDown(eKeyCode::SPACE)) {
		animFlag = true;
		index += 1;

		std::cout << index << "\n";

		if (index > 6) {
			index = 0;
		}
	}

	if (index == 0 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
	}
	else if (index == 1 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Attack", true);
	}
	else if (index == 2 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Run", true);
	}
	else if (index == 3 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Damage", true);
	}
	else if (index == 4 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"JoyResult", true);
	}
	else if (index == 5 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"RunGS", true);
	}
	else if (index == 6 && animFlag) {
		animFlag = false;
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"StandBy", true);
	}


}

void Jun::PlayerState::DebugState::Exit()
{
}
