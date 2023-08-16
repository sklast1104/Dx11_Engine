#include "BattleScene.h"
#include "Camera.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "SkeletonMecanim.h"
#include "PlayerStateMachine.h"
#include "MonsterStateMachine.h"
#include "Input.h"
#include "Light.h"
#include "Health.h"
#include "Fader.h"

#include "TransContainer.h"
#include "BattleManager.h"
#include "StageManager.h"
#include "MonsterContainer.h"

namespace Jun {

	using namespace Jun::PlayerState;

	BattleScene::BattleScene()
	{
	}

	BattleScene::~BattleScene()
	{
	}

	void BattleScene::Initialize()
	{
		MeshRenderer* mr = nullptr;

		// BackGround && UI
		{
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
		}

		// Light (나중에 지울것)
		{
			GameObject* light = new GameObject();
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}


		//Monster
		{
			

			GameObject* monParent = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::UI);
			monParent->SetName(L"MonParent");
			monParent->SetState(GameObject::eState::Active);
			monParent->AddComponent<MonsterContainer>();

			std::vector<Vector3> wavePoses;
			wavePoses.push_back(Vector3(0.6f, 0.2f, 0.3f));
			wavePoses.push_back(Vector3(1.f, 0.f, 0.2f));

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 0, true);
			}

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 1, false);
			}

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 2, false);
			}
		}

		// Princesses
		{
			Vector3 prinCessScale = { 1.f, 1.f, 1.f };
			prinCessScale *= 2.1f;

			Vector3 posOffset = { 0.f, 0.1f, 0.f };

			float runGSFrame = 0.035;

			{
				GameObject* pecorinne = object::Instantiate<GameObject>(Vector3(-0.2f, 0.2f, 0.5f) + posOffset, eLayerType::UI);

				mr = pecorinne->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = pecorinne->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Attack.atlas", 0.033f, Vector2(33, 35.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Run.atlas", 0.03f, Vector2(30.f, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Damage.atlas", 0.03f, Vector2(0, -15));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_JoyResult.atlas", 0.03f, Vector2(0, 0));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_RunGS.atlas", runGSFrame, Vector2(0, 30));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_StandBy.atlas", 0.03f, Vector2(0, 55));

				pecorinne->AddComponent<TransContainer>()->Pos = Vector3(-0.2f, 0.2f, 0.5f) + posOffset;
				pecorinne->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				pecorinne->AddComponent<BattleManager>()->xLimit = 0.9f;

				pecorinne->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* saren = object::Instantiate<GameObject>(Vector3(-0.3f, 0.f, 0.4f) + posOffset, eLayerType::UI);

				mr = saren->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = saren->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Attack.atlas", 0.033f, Vector2(18, 35.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Run.atlas", 0.03f, Vector2(0, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_Damage.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_JoyResult.atlas", 0.03f, Vector2(0, 40.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_RunGS.atlas", runGSFrame, Vector2(0, 70.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Saren\\Saren_StandBy.atlas", 0.03f, Vector2(0, -20.f));

				saren->AddComponent<TransContainer>()->Pos = Vector3(-0.3f, 0.f, 0.4f) + posOffset;
				saren->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				saren->AddComponent<BattleManager>()->xLimit = 1.f;

				saren->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* kotkoro = object::Instantiate<GameObject>(Vector3(-0.6f, 0.4f, 0.5f) + posOffset, eLayerType::UI);

				mr = kotkoro->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kotkoro->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_Attack.atlas", 0.033f, Vector2(0, 15.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_Run.atlas", 0.03f, Vector2(0, 27.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_Damage.atlas", 0.03f, Vector2(0, 10.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_JoyResult.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_RunGS.atlas", runGSFrame, Vector2(0, -5.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kotkoro\\Kotkoro_Standby.atlas", 0.03f, Vector2(0, -35.f));

				kotkoro->AddComponent<TransContainer>()->Pos = Vector3(-0.6f, 0.4f, 0.5f) + posOffset;
				kotkoro->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				kotkoro->AddComponent<BattleManager>()->xLimit = 1.3f;

				kotkoro->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* kyouka = object::Instantiate<GameObject>(Vector3(-0.9f, 0.0f, 0.4f) + posOffset, eLayerType::UI);

				mr = kyouka->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kyouka->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Attack.atlas", 0.033f, Vector2(0, 25.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Run.atlas", 0.03f, Vector2(0, 50.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_Damage.atlas", 0.03f, Vector2(0, 0.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_JoyResult.atlas", 0.03f, Vector2(0, -25.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_RunGS.atlas", runGSFrame, Vector2(0, 95.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kyouka\\Kyouka_StandBy.atlas", 0.03f, Vector2(0, 20.f));

				kyouka->AddComponent<TransContainer>()->Pos = Vector3(-0.9f, 0.0f, 0.4f) + posOffset;
				kyouka->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				kyouka->AddComponent<BattleManager>()->xLimit = 1.6f;

				kyouka->GetComponent<Transform>()->SetScale(prinCessScale);
			}

			{
				GameObject* kyaru = object::Instantiate<GameObject>(Vector3(-1.2f, 0.2f, 0.5f) + posOffset, eLayerType::UI);

				mr = kyaru->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = kyaru->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Attack.atlas", 0.033f, Vector2(0, 25.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Run.atlas", 0.03f, Vector2(0, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_Damage.atlas", 0.03f, Vector2(0, -10.f));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_JoyResult.atlas", 0.03f, Vector2(0, 20.f));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_RunGS.atlas", runGSFrame, Vector2(0, 90.f));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Kyaru\\Kyaru_StandBy.atlas", 0.03f, Vector2(0, 20.f));

				kyaru->AddComponent<TransContainer>()->Pos = Vector3(-1.2f, 0.2f, 0.5f) + posOffset;
				kyaru->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				kyaru->AddComponent<BattleManager>()->xLimit = 1.9f;

				kyaru->GetComponent<Transform>()->SetScale(prinCessScale);
			}

		}

		// Effect

		{
			GameObject* fader = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::UI);
			MeshRenderer* mr = fader->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Fader_Material"));
			fader->AddComponent<Fader>();

			fader->GetComponent<Transform>()->SetScale(Vector3(16.0f, 9.0f, 1.0f) * 0.4);
		}

		// Logic 

		{
			GameObject* stageManager = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::Logic);
			stageManager->AddComponent<StageManager>();
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

	void BattleScene::InitMoster(Vector3 pos, GameObject* parent, int index, bool isActive)
	{
		Vector3 monsterOffset = { -0.1f, 0.f, 0.f };

		MonsterContainer* container = parent->GetComponent<MonsterContainer>();

		GameObject* ratMon = new GameObject;
		ratMon->GetComponent<Transform>()->SetPosition(pos + monsterOffset);

		if (!isActive)
			ratMon->SetState(GameObject::eState::Dead);

		MeshRenderer* mr = ratMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		SkeletonMecanim* anim = ratMon->AddComponent<SkeletonMecanim>();
		anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Idle.atlas", 0.033f);
		anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Run.atlas", 0.033f);
		anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Damage.atlas", 0.033f, Vector2(39.f, 17.f));
		anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Attack.atlas", 0.033f);

		ratMon->AddComponent<TransContainer>()->Pos = pos + monsterOffset;
		ratMon->AddComponent<MonsterStateMachine>();
		ratMon->AddComponent<Health>();

		ratMon->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f) * 2.7f);

		parent->AddChild(ratMon);

		GameObject* hpUI = new GameObject;

		mr = hpUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_HpUI_Material"));

		hpUI->GetComponent<Transform>()->SetScale(Vector3(1.3f, 0.2f, 1.f) * 0.17f);
		hpUI->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.15f, 0.f));

		ratMon->AddChild(hpUI);

		GameObject* hpVal = new GameObject;

		mr = hpVal->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_HpValTest_Material"));

		hpVal->GetComponent<Transform>()->SetScale(Vector3(0.9f, 0.52f, 1.f));
		hpVal->GetComponent<Transform>()->SetPosition(Vector3(-0.015f, -0.02f, -0.1f));

		hpUI->AddChild(hpVal);

		

		if (index == 0)
			container->wave1.push_back(ratMon);
		else if (index == 1)
			container->wave2.push_back(ratMon);
		else if (index == 2)
			container->wave3.push_back(ratMon);
	}

}