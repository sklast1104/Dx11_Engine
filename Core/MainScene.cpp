#include "MainScene.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Renderer.h"
#include "VideoPlayer.h"

namespace Jun {



	MainScene::MainScene()
	{
	}

	MainScene::~MainScene()
	{
	}

	void MainScene::Initialize()
	{
		GameObject* backGround
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::UI);

		MeshRenderer* mr = backGround->AddComponent<MeshRenderer>();
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

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}
	}

	void MainScene::Update()
	{
		Scene::Update();
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