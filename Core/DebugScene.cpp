#include "DebugScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "SkeletonMecanim.h"
#include "Transform.h"
#include "Light.h"

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
		{
			GameObject* light = new GameObject();
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		GameObject* backGround = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 1.f), eLayerType::UI);

		MeshRenderer* mr = backGround->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBG_Material"));

		backGround->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 3.f) * 0.4f);

		// Debug Princess
		{
			GameObject* pecorinne = object::Instantiate<GameObject>(Vector3(0.f, 2.f, 0.f), eLayerType::UI);

			MeshRenderer* mr = pecorinne->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			SkeletonMecanim* anim = pecorinne->AddComponent<SkeletonMecanim>();
			anim->Create(L"Test_Pecorinne", L"..\\Resources\\Texture\\Spine\\Test_Pecorinne\\TestAnim.atlas", 0.035f);
			anim->PlayAnimation(L"Test_Pecorinne", true);

			//anim = pecorinne->AddComponent<SkeletonMecanim>();
			//anim->Create(L"AttackAnim", L"..\\Resources\\Texture\\Spine\\Test_Pecorinne\\AttackAnim.atlas", 0.035f);

			pecorinne->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f) * 5);
		}

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();

			
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