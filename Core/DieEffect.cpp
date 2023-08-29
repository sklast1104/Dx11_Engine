#include "DieEffect.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GameObject.h"
#include "MyTime.h"
#include "SpriteAnimMaterial.h"
#include "MyMath.h"

namespace Jun {

	using namespace Jun::math;

	void DieEffect::Initialize()
	{
		flag = false;
		delay = 1.f;
	}

	void DieEffect::Start()
	{
		MeshRenderer* render = GetOwner()->GetComponent<MeshRenderer>();
		Material* mt = render->GetMaterial().get();
		material = (SpriteAnimMaterial*)mt;
	}

	void DieEffect::Update()
	{
		if (flag) {
			elapsedTime += Time::DeltaTime();

			if (elapsedTime > delay) {
				flag = false;
			}

			float start = 1.f;
			float end = 0.f;

			float lerpValue = Lerp(start, end, elapsedTime / delay);

			material->color = Vector4(1.f, 1.f, 1.f, lerpValue);
		}
	}

	void DieEffect::LateUpdate()
	{
	}

	void DieEffect::Render()
	{
	}

	void DieEffect::PlayEffect()
	{
		flag = true;
		material->color = Vector4(1.f, 1.f, 1.f, 1.f);
	}

}