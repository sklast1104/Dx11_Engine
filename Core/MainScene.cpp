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
		GameObject* player
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VideoMaterial"));

		videoPlayer = player->AddComponent<VideoPlayer>();
		videoPlayer->Create("../data/demo.mp4");

		player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		Transform* transform = player->GetComponent<Transform>();
		transform->SetScale(Vector3(8.0f, 6.0f, 1.0f));

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