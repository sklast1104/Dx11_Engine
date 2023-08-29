#include "MonsterDieState.h"
#include "GameObject.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "DieEffect.h"

namespace Jun {



	void MonsterDieState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Die", false);
		flag = true;
		delay = 1.f;
		elapsedTime = 0.f;

		DieEffect* dieEffect = owner->GetComponent<DieEffect>();
		dieEffect->PlayEffect();
	}

	void MonsterDieState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (elapsedTime > delay && flag) {
			flag = false;

			owner->SetState(GameObject::eState::Dead);

		}
	}

	void MonsterDieState::Exit()
	{
	}

}