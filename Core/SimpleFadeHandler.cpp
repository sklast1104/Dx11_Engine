#include "SimpleFadeHandler.h"
#include "MeshRenderer.h"
#include "SimpleFadeMaterial.h"
#include "GameObject.h"
#include "MyTime.h"
#include "SceneManager.h"

namespace Jun {

	void SimpleFadeHandler::Initialize()
	{
		MeshRenderer* render = GetOwner()->GetComponent<MeshRenderer>();
		mt = (SimpleFadeMaterial*)render->GetMaterial().get();

		// 1 ~ 0
		mt->fadeVal = 0.f;

		speed = 1.f;

		elapsedTime = 0.f;
		flag = false;
		flag2 = false;
	}

	void SimpleFadeHandler::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (mt->fadeVal >= 1.f) {
			flag = false;
			mt->fadeVal = 0.f;

			SceneManager::LoadScene(L"MenuScene");
		}

		if (flag) {
			mt->fadeVal += Time::DeltaTime() * speed;
		}
	}

	void SimpleFadeHandler::LateUpdate()
	{
	}

	void SimpleFadeHandler::Render()
	{
	}

	void SimpleFadeHandler::StartFade()
	{
		mt->fadeVal = 0.f;
		flag = true;
	}

}