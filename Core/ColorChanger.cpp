#include "ColorChanger.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "SpriteAnimMaterial.h"
#include "MyTime.h"

namespace Jun {

	void ColorChanger::Initialize()
	{
		flag = false;
		delay = 0.3f;
	}

	void ColorChanger::Start()
	{
		MeshRenderer* render = GetOwner()->GetComponent<MeshRenderer>();
		Material* mt = render->GetMaterial().get();
		material = (SpriteAnimMaterial*)mt;
	}

	void ColorChanger::Update()
	{
		if (flag) {
			elapsedTime += Time::DeltaTime();
		}

		if (elapsedTime > delay) {
			flag = false;
			material->color = Vector4(1.f, 1.f, 1.f, 1.f);
		}
	}

	void ColorChanger::LateUpdate()
	{
	}

	void ColorChanger::Render()
	{
	}

	void ColorChanger::AttackedEffect()
	{
		elapsedTime = 0.f;
		flag = true;
		material->color = Vector4(1.f, 0.f, 0.f, 1.f);
	}

}