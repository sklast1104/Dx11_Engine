#include "MainScene.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Renderer.h"
#include "VideoPlayer.h"
#include "Input.h"
#include "UI.h"
#include "MainUIHandler.h"
#include "SimpleFadeHandler.h"

namespace Jun {



	MainScene::MainScene()
	{
	}

	MainScene::~MainScene()
	{
	}

	void MainScene::Initialize()
	{
		MeshRenderer* mr;

		GameObject* backGround
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::UI);

		mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VideoMaterial"));

		VideoPlayer* videoPlayer = backGround->AddComponent<VideoPlayer>();
		videoPlayer->Create("../data/Title.mp4");

		backGround->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
		Transform* transform = backGround->GetComponent<Transform>();
		transform->SetScale(Vector3(16.0f, 9.0f, 1.0f) * 0.4);

		GameObject* titleUI
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.f), eLayerType::UI);

		mr = titleUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Btn_Material"));

		titleUI->GetComponent<Transform>()->SetScale(Vector3(16.0f, 9.0f, 1.f) * 0.4f);

		GameObject* title
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.f), eLayerType::UI);

		mr = title->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Title_Material"));

		title->GetComponent<Transform>()->SetPosition(Vector3(0, -0.83, 0.9f));
		title->GetComponent<Transform>()->SetScale(Vector3(4.61f, 1.6f, 1.f) * 0.8f);

		//GameObject* collider
		//	= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 5.f), eLayerType::UI);

		////collider->AddComponent<Collider2D>();
		//collider->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);
		//collider->AddComponent<UI>();
		//collider->AddComponent<MainUIHandler>();

		// Light
		{
			GameObject* light = new GameObject();
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		// Fader
		{
			GameObject* simpleFader
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -4.f), eLayerType::UI);

			mr = simpleFader->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SimpleFadeMaterial"));

			//simpleFader->AddComponent<Collider2D>();
			simpleFader->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);
			simpleFader->AddComponent<SimpleFadeHandler>();
			simpleFader->AddComponent<UI>();
			simpleFader->AddComponent<MainUIHandler>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();

			renderer::mainCamera = cameraComp;
		}
	}

	void MainScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"MenuScene");
		}
	}

	void MainScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MainScene::Render()
	{
		Scene::Render();
	}

}