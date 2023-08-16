#include "MonsterIdleState.h"
#include "SkeletonMecanim.h"

namespace Jun {

	void MonsterIdleState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
	}

	void MonsterIdleState::Update()
	{
	}

	void MonsterIdleState::Exit()
	{
	}

}