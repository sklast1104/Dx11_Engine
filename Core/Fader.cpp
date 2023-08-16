#include "Fader.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "FaderMaterial.h"
#include "MyTime.h"

namespace Jun {

	void Fader::Initialize()
	{
		MeshRenderer* render = GetOwner()->GetComponent<MeshRenderer>();
		mt = (FaderMaterial*)render->GetMaterial().get();

		// -1 ~ 1까지 천천히 페이드되게 구현
		mt->FadeVal = -1.f;

		speed = 3.f;

		elapsedTime = 0.f;
		flag = false;
	}

	void Fader::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (mt->FadeVal >= 1.f) {
			flag = false;
			mt->FadeVal = -1.f;
		}

		if (flag) {
			mt->FadeVal += Time::DeltaTime() * speed;
		}

		//mt->FadeVal += speed * Time::DeltaTime();

	}

	void Fader::LateUpdate()
	{
	}

	void Fader::Render()
	{
		// 여기서 바인드 호출
	}

	void Fader::StartFade()
	{
		mt->FadeVal = -1.f;
		flag = true;
		
	}

}