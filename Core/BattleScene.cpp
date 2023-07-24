#include "BattleScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "SkeletonMecanim.h"
#include "PlayerStateMachine.h"
#include "Input.h"

namespace Jun {



	BattleScene::BattleScene()
	{
	}

	BattleScene::~BattleScene()
	{
	}

	void BattleScene::Initialize()
	{
		MeshRenderer* mr = nullptr;

		GameObject* backGround = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 1.f), eLayerType::UI);

		mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBG_Material"));

		backGround->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 3.f) * 0.4f);

		GameObject* baseUI = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.9f), eLayerType::UI);

		mr = baseUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBaseUI_Material"));

		baseUI->GetComponent<Transform>()->SetScale(Vector3(12.9f, 7.25f, 1.f) * 0.5f);

		GameObject* princess = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.5f), eLayerType::UI);

		mr = princess->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		SkeletonMecanim* anim = princess->AddComponent<SkeletonMecanim>();
		anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Pecorinne_Idle.atlas", 0.04f);
		anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Pecorinne_Attack.atlas", 0.025f, Vector2(0, 35.f));
		anim->Create(L"Walk", L"..\\Resources\\Texture\\Spine\\Pecorinne\\walk\\Pecorinne_walk.atlas", 0.03f);

		princess->AddComponent<PlayerStateMachine>();

		//anim->PlayAnimation(L"Idle", true);

		princess->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f) * 2.f);
		princess->AddComponent<Collider2D>();

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
		}
	}

	void BattleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"MainScene");
		}
	}

	void BattleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BattleScene::Render()
	{
		Scene::Render();
	}

}