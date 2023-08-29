#include "SkillState.h"
#include "SkeletonMecanim.h"
#include "GameObject.h"
#include "Object.h"

namespace Jun::PlayerState {

	using namespace Jun::object;

	void SkillState::Enter()
	{
		//SkeletonMecanim* mecanim = owner->GetComponent<SkeletonMecanim>();
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Skill", true);
		GameObject* bg = FindObjectByName(L"Peco_Skill2_Bg");
		bg->GetComponent<Transform>()->SetPosition(0.f, 0.f, -2.5f);

		GameObject* peco = FindObjectByName(L"peco");
		Transform* pecoTr = peco->GetComponent<Transform>();

		Vector3 pos = pecoTr->GetPosition();
		pos.z = -3.f;

		pecoTr->SetPosition(pos);
	}

	void SkillState::Update()
	{
	}

	void SkillState::Exit()
	{
	}

}