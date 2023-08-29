#include "MenuScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "SceneManager.h"
#include "Input.h"
#include "SimpleFadeHandler.h"
#include "UI.h"


namespace Jun {



	MenuScene::MenuScene()
	{
	}

	MenuScene::~MenuScene()
	{
	}

	void MenuScene::Initialize()
	{
		MeshRenderer* mr = nullptr;

		GameObject* backGround
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.f), eLayerType::UI);

		mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MenuBG_Material"));

		backGround->GetComponent<Transform>()->SetScale(Vector3(1.1f, 1.0f, 1.f) * 6);
		backGround->SetName(L"backgroud");

		GameObject* character = object::Instantiate<GameObject>(Vector3(-0.55f, -0.1f, 0.9f), eLayerType::UI);

		mr = character->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Pecorinne_Material"));

		character->GetComponent<Transform>()->SetScale(Vector3(9.3f, 6.6f, 1.f) * 0.5f);
		character->SetName(L"Character");

		GameObject* BaseUI = object::Instantiate<GameObject>(Vector3(0.05f, 0.15f, 0.8f), eLayerType::UI);

		mr = BaseUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UI2_Material"));

		BaseUI->GetComponent<Transform>()->SetScale(Vector3(13.0f, 6.4f, 1.f) * 0.5f);
		BaseUI->SetName(L"BaseUI");

		GameObject* navUI = object::Instantiate<GameObject>(Vector3(0.f, -1.58f, 0.7f), eLayerType::UI);

		mr = navUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bottom_nav_mat"));

		navUI->GetComponent<Transform>()->SetScale(Vector3(12.5f, 1.1f, 1.f) * 0.5f);
		navUI->SetName(L"nav");
		

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
		}

		// Fader
		{
			GameObject* simpleFader
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -8.f), eLayerType::UI);

			mr = simpleFader->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SimpleFadeMaterial"));

			simpleFader->AddComponent<Collider2D>();
			simpleFader->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.2f);
			simpleFader->AddComponent<SimpleFadeHandler>();
			simpleFader->AddComponent<UI>();
			//simpleFader->AddComponent<MainUIHandler>();
		}

		// UI Coll
		//{
		//	GameObject* uiColl = object::Instantiate<GameObject>(Vector3(0.f, -2.f, -2.f), eLayerType::UI);
		//	uiColl->AddComponent<Collider2D>();
		//}
	}

	void MenuScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"QuestScene");
		}
	}

	void MenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void MenuScene::Render()
	{
		Scene::Render();
	}

}