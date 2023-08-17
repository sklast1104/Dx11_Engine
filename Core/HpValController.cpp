#include "HpValController.h"
#include "MeshRenderer.h"
#include "GameObject.h"

#include "HpBarMaterial.h"

namespace Jun {

	void HpValController::Initialize()
	{
	}

	void HpValController::Start()
	{
		MeshRenderer* renderer = GetOwner()->GetComponent<MeshRenderer>();
		Material* mt =  renderer->GetMaterial().get();
		material = (HpBarMaterial*)mt;
	}

	void HpValController::Update()
	{
	}

	void HpValController::LateUpdate()
	{
	}

	void HpValController::Render()
	{
	}

	void HpValController::DealDamage(float damage)
	{
	}

	void HpValController::SetPercent(float percent)
	{
		material->hpPercent = percent;
	}

}