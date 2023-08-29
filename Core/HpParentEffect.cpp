#include "HpParentEffect.h"
#include "MyTime.h"
#include "GameObject.h"

namespace Jun {

	void HpParentEffect::Initialize()
	{
		flag = false;
		delay = 0.5f;
		elapsedTime = 0.f;
	}

	void HpParentEffect::Start()
	{
		flag = false;
		elapsedTime = 0.f;
	}

	void HpParentEffect::Update()
	{
		if (flag) {
			elapsedTime += Time::DeltaTime();

			if (elapsedTime > delay) {
				flag = false;
				GetOwner()->SetState(GameObject::eState::Dead);
			}
		}
	}

	void HpParentEffect::LateUpdate()
	{
	}

	void HpParentEffect::Render()
	{
	}

	void HpParentEffect::PlayEffect()
	{
		flag = true;
	}

}