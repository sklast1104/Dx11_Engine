#include "BattleScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "SkeletonMecanim.h"
#include "PlayerStateMachine.h"
#include "Input.h"
#include "Light.h"

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

		// Light (나중에 지울것)
		{
			GameObject* light = new GameObject();
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		// Princesses
		{
			Vector3 prinCessScale = { 1.f, 1.f, 1.f };
			prinCessScale *= 2.1f;

			Vector3 posOffset = { 0.f, 0.1f, 0.f };

			float runGSFrame = 0.035;

			{
				GameObject* pecorinne = object::Instantiate<GameObject>(Vector3(0.f, 0.2f, 0.5f) + posOffset, eLayerType::UI);

				mr = pecorinne->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = pecorinne->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Attack.atlas", 0.025f, Vector2(0, 35.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Run.atlas", 0.03f, Vector2(0, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Damage.atlas", 0.03f, Vector2(0, -15));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_JoyResult.atlas", 0.03f, Vector2(0, 0));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_RunGS.atlas", runGSFrame, Vector2(0, 30));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_StandBy.atlas", 0.03f, Vector2(0, 65));

				pecorinne->AddComponent<PlayerStateMachine>();

				pecorinne->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* saren = object::Instantiate<GameObject>(Vector3(-0.3f, 0.f, 0.4f) + posOffset, eLayerType::UI);

				mr = saren->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = saren->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Attack.atlas", 0.025f, Vector2(0, 35.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Run.atlas", 0.03f, Vector2(0, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Damage.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_JoyResult.atlas", 0.03f, Vector2(0, 40.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_RunGS.atlas", runGSFrame, Vector2(0, 70.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_StandBy.atlas", 0.03f, Vector2(0, -5.f));

				saren->AddComponent<PlayerStateMachine>();

				saren->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* kotkoro = object::Instantiate<GameObject>(Vector3(-0.6f, 0.4f, 0.5f) + posOffset, eLayerType::UI);

				mr = kotkoro->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kotkoro->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_Attack.atlas", 0.025f, Vector2(0, 15.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_Run.atlas", 0.03f, Vector2(0, 27.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_Damage.atlas", 0.03f, Vector2(0, 10.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_JoyResult.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_RunGS.atlas", runGSFrame, Vector2(0, -5.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kokoro_Stanby.atlas", 0.03f, Vector2(0, -35.f));

				kotkoro->AddComponent<PlayerStateMachine>();

				kotkoro->GetComponent<Transform>()->SetScale(prinCessScale);
			}
			
			{
				GameObject* kyouka = object::Instantiate<GameObject>(Vector3(-0.9f, 0.0f, 0.4f) + posOffset, eLayerType::UI);

				mr = kyouka->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kyouka->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Attack.atlas", 0.025f, Vector2(0, 25.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Run.atlas", 0.03f, Vector2(0, 50.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Damage.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_JoyResult.atlas", 0.03f, Vector2(0, -25.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_RunGS.atlas", runGSFrame, Vector2(0, 95.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_StandBy.atlas", 0.03f, Vector2(0, 40.f));

				kyouka->AddComponent<PlayerStateMachine>();

				kyouka->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* kyaru = object::Instantiate<GameObject>(Vector3(-1.2f, 0.2f, 0.5f) + posOffset, eLayerType::UI);

				mr = kyaru->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kyaru->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Attack.atlas", 0.025f, Vector2(0, 25.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Run.atlas", 0.03f, Vector2(0, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Damage.atlas", 0.03f, Vector2(0, -10.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Joy.atlas", 0.03f, Vector2(0, 20.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_RunGS.atlas", runGSFrame, Vector2(0, 90.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_StanBy.atlas", 0.03f, Vector2(0, 30.f));

				kyaru->AddComponent<PlayerStateMachine>();

				kyaru->GetComponent<Transform>()->SetScale(prinCessScale);
			}

		}


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