#include "QuestMapScene.h"
#include "Shader.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Input.h"

namespace Jun {



	QuestMapScene::QuestMapScene()
	{
	}

	QuestMapScene::~QuestMapScene()
	{
	}

	void QuestMapScene::Initialize()
	{
		GameObject* backGround
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::UI);

		MeshRenderer* mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"QuestMap_WorldMap_Material"));

		backGround->GetComponent<Transform>()->SetScale(Vector3(16.0f, 9.0f, 1.0f) * 0.4);

		GameObject* baseUI
			= object::Instantiate<GameObject>(Vector3(0.0f, 0.03f, 0.9f), eLayerType::UI);

		mr = baseUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Quest_QuestMapUI_Edit_Material"));

		baseUI->GetComponent<Transform>()->SetScale(Vector3(12.7f, 7.0f, 1.0f) * 0.5f);

		GameObject* TopNav = object::Instantiate<GameObject>(Vector3(1.35f, 1.5f, 0.7f), eLayerType::UI);

		mr = TopNav->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Quest_TopNav_Alpha_Material"));

		TopNav->GetComponent<Transform>()->SetScale(Vector3(7.3f, 0.7f, 1.f) * 0.5f);

		GameObject* navUI = object::Instantiate<GameObject>(Vector3(0.f, -1.58f, 0.7f), eLayerType::UI);

		mr = navUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bottom_nav_mat"));

		navUI->GetComponent<Transform>()->SetScale(Vector3(12.5f, 1.1f, 1.f) * 0.5f);

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
		}
	}

	void QuestMapScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"BattleScene2");
		}
	}

	void QuestMapScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void QuestMapScene::Render()
	{
		Scene::Render();
	}

}