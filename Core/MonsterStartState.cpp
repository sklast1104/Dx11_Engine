#include "MonsterStartState.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "MyTime.h"
#include "MyMath.h"
#include "MonsterStateMachine.h"
#include "TransContainer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "HpBarMaterial.h"
#include "HpValController.h"

#include <iostream>

namespace Jun {

	void MonsterStartState::Enter()
	{
		transform = owner->GetComponent<Transform>();

		destPos = owner->GetComponent<TransContainer>()->Pos;

		//destPos = transform->GetPosition();

		transform->SetPosition(destPos + backOffset);

		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Run", true);

		elapsedTime = 0.f;

		// Material Edit
		{
			owner->GetComponentInChild<HpValController>();
			GameObject* hpUI = owner->GetComponentInChild<HpValController>()->GetOwner();
			

			MeshRenderer* renderer = hpUI->GetComponent<MeshRenderer>();
			Material* mt = renderer->GetMaterial().get();
			HpBarMaterial* material = (HpBarMaterial*)mt;

			material->hpPercent = 1.f;
		}
	}

	void MonsterStartState::Update()
	{
		elapsedTime += Time::DeltaTime();

		float dist = Vector3::Distance(destPos, transform->GetPosition());

		if (dist < 0.1f) {
			MonsterStateMachine* machine = owner->GetComponent<MonsterStateMachine>();
			machine->SwitchState(machine->stateMap[L"StandByState"].get());
		}

		Vector3 movVec = dir * Time::DeltaTime() * speed;

		transform->SetPosition(transform->GetPosition() + movVec);

	}

	void MonsterStartState::Exit()
	{
	}

}