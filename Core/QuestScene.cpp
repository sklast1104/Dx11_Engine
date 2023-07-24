#include "QuestScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "VideoPlayer.h"
#include "Resources.h"

namespace Jun {



	QuestScene::QuestScene()
	{
	}

	QuestScene::~QuestScene()
	{
	}

	void QuestScene::Initialize()
	{
		GameObject* backGround
			= object::Instantiate<GameObject>(Vector3(-1.5f, 0.0f, 1.f), eLayerType::UI);

		MeshRenderer* mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VideoMaterial"));

		VideoPlayer* videoPlayer = backGround->AddComponent<VideoPlayer>();
		videoPlayer->Create("../data/Quest.mp4");

		//backGround->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.f));
		Transform* transform = backGround->GetComponent<Transform>();
		transform->SetScale(Vector3(16.0f, 9.0f, 1.0f) * 0.4);

		GameObject* navUI = object::Instantiate<GameObject>(Vector3(0.f, -1.58f, 0.7f), eLayerType::UI);

		mr = navUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Bottom_nav_mat"));

		navUI->GetComponent<Transform>()->SetScale(Vector3(12.5f, 1.1f, 1.f) * 0.5f);

		GameObject* mainPanel = object::Instantiate<GameObject>(Vector3(2.f, 0.f, 0.8f), eLayerType::UI);

		mr = mainPanel->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Quest_MainPanel_Material"));

		mainPanel->GetComponent<Transform>()->SetScale(Vector3(5.92f, 7.27f, 1.f) * 0.5f);

		GameObject* questBtns = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.7f), eLayerType::UI);
		
		mr = questBtns->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"QuestBtns_Material"));

		questBtns->GetComponent<Transform>()->SetScale(Vector3(12.9f, 7.2f, 1.f) * 0.5f);

		GameObject* TopNav = object::Instantiate<GameObject>(Vector3(1.35f, 1.5f, 0.6f), eLayerType::UI);

		mr = TopNav->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Quest_TopNav_Alpha_Material"));

		TopNav->GetComponent<Transform>()->SetScale(Vector3(7.3f, 0.7f, 1.f) * 0.5f);

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
		}
	}

	void QuestScene::Update()
	{
		Scene::Update();
	}

	void QuestScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void QuestScene::Render()
	{
		Scene::Render();
	}

}