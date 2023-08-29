#include "DebugScene.h"
#include "Light.h"
#include "Object.h"
#include "SkeletonMecanim.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Resources.h"
#include "PlayerStateMachine.h"
#include "CameraScript.h"

namespace Jun {

	DebugScene::DebugScene()
	{
	}

	DebugScene::~DebugScene()
	{
	}

	void DebugScene::Initialize()
	{
		// Light (나중에 지울것)
		//{
		//	GameObject* light = new GameObject();
		//	AddGameObject(eLayerType::Light, light);
		//	Light* lightComp = light->AddComponent<Light>();
		//	lightComp->SetType(eLightType::Directional);
		//	lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		//}

		MeshRenderer* mr = nullptr;

		GameObject* backGround = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 1.f), eLayerType::UI);

		mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBG_Material"));

		backGround->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 3.f) * 0.4f);

		{
			GameObject* pecorinne = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::UI);

			MeshRenderer* mr = pecorinne->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			SkeletonMecanim* anim = pecorinne->AddComponent<SkeletonMecanim>();
			anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Test_Pecorinne\\AttackAnim.atlas", 0.033f, Vector2(0, -0.f));
			anim->PlayAnimation(L"Attack", true);

			Vector3 prinCessScale = { 1.f, 1.f, 1.f };
			prinCessScale *= 6.f;
			pecorinne->GetComponent<Transform>()->SetScale(prinCessScale);

			//pecorinne->GetComponent<Transform>()->SetScale(prinCessScale);
		}

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();
		}
	}

	void DebugScene::Update()
	{
		Scene::Update();
	}

	void DebugScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void DebugScene::Render()
	{
		Scene::Render();
	}
}