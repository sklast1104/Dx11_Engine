#include "PortraitHandler.h"
#include "GameObject.h"
#include "Object.h"
#include "VideoPlayer.h"
#include "MyTime.h"
#include "Health.h"
#include "Camera.h"
#include "PlayerStateMachine.h"

namespace Jun {

	using namespace Jun::PlayerState;
	using namespace Jun::object;

	void PortraitHandler::Initialize()
	{

	}

	void PortraitHandler::Start()
	{
		elapsed = 0.f;
		delay = 2.5f;
		flag = false;
		video = FindObjectOfType<VideoPlayer>()->GetOwner();
	}

	void PortraitHandler::Update()
	{
		if (flag) {
			elapsed += Time::DeltaTime();
		}

		if (elapsed > delay && flag) {
			flag = false;
			video->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 2.f));
			video->GetComponent<VideoPlayer>()->Pause();

			GameObject* mainCamera = FindObjectByName(L"Main_Camera");
			Camera* cam = mainCamera->GetComponent<Camera>();

			cam->TurnLayerMask(eLayerType::UI, false);
			cam->SetSize(4.3f);

			// 플레이어 보내기
			GameObject* peco = FindObjectByName(L"peco");
			PlayerStateMachine* machine = peco->GetComponent<PlayerStateMachine>();

			machine->SwitchState(machine->stateMap[L"SkillState"].get());
		}
	}

	void PortraitHandler::LateUpdate()
	{
	}

	void PortraitHandler::Render()
	{
	}

	void PortraitHandler::MouseLbtnDown()
	{
		std::vector<Health*> healthObjs = FindObjectsOfType<Health>();

		for (auto obj : healthObjs) {
			obj->GetOwner()->SetState(GameObject::eState::Dead);
		}
		GameObject* peco = FindObjectByName(L"peco");
		peco->SetState(GameObject::eState::Active);

		video->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -2.f));
		video->GetComponent<VideoPlayer>()->Resume();
		flag = true;
	}

}