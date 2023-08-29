#include "BattleScene2.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Renderer.h"
#include "Object.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "MonsterContainer.h"
#include "SpriteAnimMaterial.h"
#include "ColorChanger.h"
#include "DieEffect.h"
#include "SkeletonMecanim.h"
#include "TransContainer.h"
#include "MonsterStateMachine.h"
#include "Health.h"
#include "HpParentEffect.h"
#include "HpValController.h"
#include "PlayerStateMachine.h"
#include "BattleManager.h"
#include "Fader.h"
#include "MonsterBattleManager.h"
#include "PortraitHandler.h"
#include "UI.h"
#include "VideoPlayer.h"
#include "PostProcess.h"
#include "Input.h"

namespace Jun {

	using namespace Jun::PlayerState;

	BattleScene2::BattleScene2()
	{
	}

	BattleScene2::~BattleScene2()
	{
	}

	void BattleScene2::Initialize()
	{
		MeshRenderer* mr = nullptr;

		// Light (나중에 지울것)
		{
			//GameObject* light = new GameObject();
			//AddGameObject(eLayerType::Light, light);
			//Light* lightComp = light->AddComponent<Light>();
			//lightComp->SetType(eLightType::Directional);
			//lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		{
			GameObject* backGround = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 1.f), eLayerType::Default);

			mr = backGround->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBG_Material"));

			backGround->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 3.f) * 0.4f);
			backGround->SetName(L"background");

			GameObject* baseUI = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -1.f), eLayerType::UI);

			mr = baseUI->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Battle_BattleBaseUI_Material"));

			baseUI->GetComponent<Transform>()->SetScale(Vector3(12.9f, 7.25f, 1.f) * 0.5f);
			baseUI->SetName(L"baseUI");

			GameObject* portraitPanel = object::Instantiate<GameObject>(Vector3(0.f, -1.1f, -1.1f), eLayerType::UI);

			mr = portraitPanel->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Battle_PortraitPanel_Material"));

			portraitPanel->GetComponent<Transform>()->SetScale(Vector3(7.8f, 1.9f, 1.f) * 0.5f);
			portraitPanel->SetName(L"PortraitPanel");

			{
				for (int i = 0; i < 5; i++) {
					GameObject* portraitCol = object::Instantiate<GameObject>(Vector3(0.f, -1.1f, -1.1f), eLayerType::UI);
					portraitCol->SetName(L"portraitCol" + std::to_wstring(i));
					//portraitCol->AddComponent<Collider2D>();
					portraitCol->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f) * 0.6f);
					portraitCol->GetComponent<Transform>()->SetPosition(-1.6f + i * 0.8f, -1.f, -1.2f);
					portraitCol->AddComponent<UI>();

					if (i == 4) {
						portraitCol->AddComponent<PortraitHandler>();
					}

					

					//portraitPanel->AddChild(portraitCol);
				}
			}
		}

		//Monster
		{
			GameObject* monParent = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.0f), eLayerType::Default);
			monParent->SetName(L"MonParent");
			monParent->SetState(GameObject::eState::Active);
			monParent->AddComponent<MonsterContainer>();

			std::vector<Vector3> wavePoses;
			wavePoses.push_back(Vector3(0.6f, 0.2f, 0.3f));
			wavePoses.push_back(Vector3(1.f, 0.f, 0.2f));

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 0, true, i);
			}

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 1, false, i);
			}

			for (int i = 0; i < 2; i++) {
				InitMoster(wavePoses[i], monParent, 2, false, i);
			}
		}

		// Princesses
		{
			Vector3 prinCessScale = { 1.f, 1.f, 1.f };
			prinCessScale *= 2.7f;

			Vector3 posOffset = { 0.f, 0.1f, 0.f };

			float runGSFrame = 0.035;

			{
				GameObject* pecorinne = object::Instantiate<GameObject>(Vector3(-0.f, 0.2f, 0.5f) + posOffset, eLayerType::Default);

				mr = pecorinne->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				SkeletonMecanim* anim = pecorinne->AddComponent<SkeletonMecanim>();
				anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Idle.atlas", 0.04f);
				anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Attack.atlas", 0.033f, Vector2(33, 35.f));
				anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Run.atlas", 0.03f, Vector2(40.f, 45.f));
				anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Damage.atlas", 0.03f, Vector2(0, -15));
				anim->Create(L"JoyResult", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_JoyResult.atlas", 0.03f, Vector2(30, 0));
				anim->Create(L"RunGS", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_RunGS.atlas", runGSFrame, Vector2(15, 30));
				anim->Create(L"StandBy", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_StandBy.atlas", 0.03f, Vector2(15, 55));
				anim->Create(L"Skill", L"..\\Resources\\Texture\\Spine\\Pecorinne\\Peco_Skill.atlas", 0.03f, Vector2(0, 0));

				pecorinne->AddComponent<TransContainer>()->Pos = Vector3(-0.f, 0.2f, 0.5f) + posOffset;
				pecorinne->AddComponent<Jun::PlayerState::PlayerStateMachine>();
				pecorinne->AddComponent<BattleManager>()->xLimit = 0.7f;

				pecorinne->GetComponent<Transform>()->SetScale(prinCessScale);
				pecorinne->AddComponent<Health>();

				pecorinne->SetName(L"peco");
			}

			{
				GameObject* saren = object::Instantiate<GameObject>(Vector3(-0.3f, 0.f, 0.4f) + posOffset, eLayerType::Default);

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
				saren->AddComponent<Health>();
			}

			{
				GameObject* kotkoro = object::Instantiate<GameObject>(Vector3(-0.6f, 0.4f, 0.5f) + posOffset, eLayerType::Default);

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
				kotkoro->AddComponent<Health>();
			}

			{
				GameObject* kyouka = object::Instantiate<GameObject>(Vector3(-0.9f, 0.0f, 0.4f) + posOffset, eLayerType::Default);

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
				kyouka->AddComponent<Health>();
			}

			{
				GameObject* kyaru = object::Instantiate<GameObject>(Vector3(-1.2f, 0.2f, 0.5f) + posOffset, eLayerType::Default);

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
				kyaru->AddComponent<Health>();
			}

		}

		// Effect

		{
			GameObject* fader = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.f), eLayerType::Default);
			MeshRenderer* mr = fader->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Fader_Material"));
			fader->AddComponent<Fader>();

			fader->GetComponent<Transform>()->SetScale(Vector3(16.0f, 9.0f, 1.0f) * 0.4);

			GameObject* pecoVideo
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.f), eLayerType::Default);

			pecoVideo->SetName(L"pecoVideo");

			mr = pecoVideo->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"VideoMaterial"));

			VideoPlayer* videoPlayer = pecoVideo->AddComponent<VideoPlayer>();
			videoPlayer->Create("../data/Pecorinne.mp4");
			videoPlayer->Pause();

			//backGround->AddComponent<Collider2D>();
			Transform* transform = pecoVideo->GetComponent<Transform>();
			transform->SetScale(Vector3(9.6f, 7.2f, 1.0f) * 0.7);

			pecoVideo->SetState(GameObject::eState::Active);

			

			{
				GameObject* parent = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 2.5f), eLayerType::Default);
				parent->SetName(L"Peco_Skill2_Bg");

				GameObject* bgSliderEffect; //= object::Instantiate<GameObject>(Vector3(0.f, 1.f, -2.5f), eLayerType::Default);
				bgSliderEffect = new GameObject;
				bgSliderEffect->GetComponent<Transform>()->SetPosition(0.f, 1.f, 0.f);
				mr = bgSliderEffect->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"Battle_BgEffect_Material"));

				bgSliderEffect->GetComponent<Transform>()->SetScale(Vector3(16.f, 4.f, 1.f) * 0.4f);

				parent->AddChild(bgSliderEffect);

				GameObject* bgSliderEffect2; //= object::Instantiate<GameObject>(Vector3(0.f, -2.f, -2.6f), eLayerType::Default);
				bgSliderEffect2 = new GameObject;
				bgSliderEffect2->GetComponent<Transform>()->SetPosition(0.f, -2.f, -0.2f);
				mr = bgSliderEffect2->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"Battle_BgEffect_Material"));

				bgSliderEffect2->GetComponent<Transform>()->SetScale(Vector3(16.f, 4.f, 1.f) * 0.4f);

				parent->AddChild(bgSliderEffect2);

				GameObject* gradationEffect; // = object::Instantiate<GameObject>(Vector3(0.f, 2.f, -2.6f), eLayerType::Default);
				gradationEffect = new GameObject;
				gradationEffect->GetComponent<Transform>()->SetPosition(0.f, 2.f, -0.1f);

				mr = gradationEffect->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"Battle_GradationEffect_Material"));

				gradationEffect->GetComponent<Transform>()->SetScale(Vector3(16.f, 4.f, 1.f) * 0.4f);

				parent->AddChild(gradationEffect);

				GameObject* gradationEffect2; // = object::Instantiate<GameObject>(Vector3(0.f, 2.f, -2.6f), eLayerType::Default);
				gradationEffect2 = new GameObject;
				gradationEffect2->GetComponent<Transform>()->SetPosition(0.f, -2.f, -0.1f);

				mr = gradationEffect2->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"Battle_GradationEffect_Material"));

				gradationEffect2->GetComponent<Transform>()->SetScale(Vector3(16.f, 4.f, 1.f) * 0.4f);

				parent->AddChild(gradationEffect2);

				GameObject* bgEffect2; // = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.4f), eLayerType::Default);
				bgEffect2 = new GameObject;
				bgEffect2->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.1f);
				mr = bgEffect2->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"Battle_BgEffect2_Material"));

				bgEffect2->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				parent->AddChild(bgEffect2);

				parent->SetState(GameObject::eState::Active);
			}
			
			//// sword effect
			//{
			//	GameObject* swordTrail = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
			//	MeshRenderer* mr = swordTrail->AddComponent<MeshRenderer>();
			//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			//	mr->SetMaterial(Resources::Find<Material>(L"Battle_SworldTrail_Material"));
			//}

			

			// Post Process
			{
				//GameObject* swordTrail = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				////swordTrail->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				//MeshRenderer* mr = swordTrail->AddComponent<MeshRenderer>();
				//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				//mr->SetMaterial(Resources::Find<Material>(L"PostProcessMaterial"));

				//swordTrail->AddComponent<PostProcess>()->slotNum = 51;
			}

			{
				GameObject* blurEffect = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				blurEffect->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				PostProcess* pp = blurEffect->AddComponent<PostProcess>();
				//pp->SetInputTexture(renderer::renderTarget);
				pp->SetInputTextures({renderer::renderTarget});
				pp->SetRenderTargets({ renderer::renderTarget->GetRTV() });

				MeshRenderer* mr = blurEffect->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SamplerMaterial"));

				pps.push_back(blurEffect);

				GameObject* redEffect = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				redEffect->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				PostProcess* pp2 = redEffect->AddComponent<PostProcess>();
				pp2->SetInputTextures({ pp->GetDestTex(0)});
				//pp2->SetInputTextures({ pp->GetDestTex()});
				pp2->SetRenderTargets({renderer::renderTarget->GetRTV()});

				mr = redEffect->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"BloomExtractMaterial"));

				//redEffect->SetState(GameObject::eState::Dead);

				pps.push_back(redEffect);

				GameObject* blur2Effect = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				blur2Effect->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				PostProcess* pp3 = blur2Effect->AddComponent<PostProcess>();
				pp3->SetInputTextures({ renderer::renderTarget });
				//pp3->SetInputTextures({ pp2->GetDestTex(0) });
				//pp3->SetInputTexture(pp2->GetDestTex());
				pp3->SetRenderTargets({ renderer::renderTarget->GetRTV() });

				mr = blur2Effect->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"BlurMaterial"));

				//blur2Effect->SetState(GameObject::eState::Dead);

				pps.push_back(blur2Effect);

				//blur2Effect->SetState(GameObject::eState::Dead);
				//GameObject* blur3Effect = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				//blur2Effect->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				//PostProcess* pp4 = blur2Effect->AddComponent<PostProcess>();
				//pp4->SetInputTextures({ renderer::renderTarget });
				////pp3->SetInputTextures({ pp2->GetDestTex(0) });
				////pp3->SetInputTexture(pp2->GetDestTex());
				//pp4->SetRenderTargets({ renderer::renderTarget->GetRTV() });

				//mr = blur3Effect->AddComponent<MeshRenderer>();
				//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				//mr->SetMaterial(Resources::Find<Material>(L"BlurMaterial"));

				//GameObject* copyFilter = object::Instantiate<GameObject>(Vector3(0.f, -0.f, -2.5f), eLayerType::Default);
				//copyFilter->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				//PostProcess* pp4 = copyFilter->AddComponent<PostProcess>();
				//pp4->SetInputTextures({ renderer::renderTarget });
				////pp4->SetInputTextures({ pp->GetDestTex(0) });
				////pp4->SetInputTexture(renderer::renderTarget);
				//pp4->SetRenderTargets({ renderer::renderTarget->GetRTV() });

				//mr = copyFilter->AddComponent<MeshRenderer>();
				//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				//mr->SetMaterial(Resources::Find<Material>(L"SamplerMaterial"));

				GameObject* combineFilter = object::Instantiate<GameObject>(Vector3(0.f, 0.f, -2.5f), eLayerType::Default);
				combineFilter->GetComponent<Transform>()->SetScale(Vector3(16.f, 9.f, 1.f) * 0.4f);

				PostProcess* pp5 = combineFilter->AddComponent<PostProcess>();
				pp5->SetInputTextures({ pp3->GetDestTex(0) });
				pp5->SetInputTextures({ renderer::renderTarget, pp->GetDestTex(0)});
				//pp4->SetInputTexture(renderer::renderTarget);
				pp5->SetRenderTargets({ renderer::renderTarget->GetRTV() });

				mr = combineFilter->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"CombineMaterial"));

				//combineFilter->SetState(GameObject::eState::Dead);

				pps.push_back(combineFilter);
			}

		}

		// Logic 

		{
			GameObject* stageManager = object::Instantiate<GameObject>(Vector3(0.f, 0.f, 0.f), eLayerType::Logic);
			stageManager->AddComponent<StageManager>();
			stageManager->AddComponent<MonsterBattleManager>();
		}

		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Camera, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->SetSize(4.7f);
		//	cameraComp->TurnLayerMask(eLayerType::UI, false);
		//	camera->SetName(L"CutScene_Camera");
		//	//camera->SetState(GameObject::eState::Dead);
		//}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			//cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			cameraComp->SetSize(5.f);
			camera->SetName(L"Main_Camera");

			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}
	}

	void BattleScene2::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::K)) {
			
			pps[index]->SetState(GameObject::eState::Dead);

			index--;

		}
	}

	void BattleScene2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BattleScene2::Render()
	{
		Scene::Render();
	}

	void BattleScene2::InitMoster(Vector3 pos, GameObject* parent, int index, bool isActive, int hpIndex)
	{
		Vector3 monsterOffset = { -0.1f, 0.f, 0.f };

		MonsterContainer* container = parent->GetComponent<MonsterContainer>();

		GameObject* ratMon = new GameObject;
		ratMon->SetName(L"rat");
		ratMon->GetComponent<Transform>()->SetPosition(pos + monsterOffset);

		if (!isActive)
			ratMon->SetState(GameObject::eState::Dead);

		MeshRenderer* mr;

		{
			std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteAnimationShader");
			std::shared_ptr<Material> material = std::make_shared<SpriteAnimMaterial>();
			material->SetRenderingMode(eRenderingMode::Transparent);
			material->SetShader(shader);

			mr = ratMon->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(material);
		}

		ratMon->AddComponent<ColorChanger>();
		ratMon->AddComponent<DieEffect>();

		SkeletonMecanim* anim = ratMon->AddComponent<SkeletonMecanim>();
		anim->Create(L"Idle", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Idle.atlas", 0.033f);
		anim->Create(L"Run", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Run.atlas", 0.033f);
		anim->Create(L"Damage", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Damage.atlas", 0.033f, Vector2(39.f, 17.f));
		anim->Create(L"Attack", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Attack.atlas", 0.033f, Vector2(40.f, -40.f));
		anim->Create(L"Die", L"..\\Resources\\Texture\\Spine\\Monster\\Rat\\Rat_Die.atlas", 0.04f, Vector2(-40.f, 80.f));

		ratMon->AddComponent<TransContainer>()->Pos = pos + monsterOffset;
		ratMon->AddComponent<MonsterStateMachine>();
		ratMon->AddComponent<Health>();

		ratMon->GetComponent<Transform>()->SetScale(Vector3(1.f, 1.f, 1.f) * 3.4f);

		parent->AddChild(ratMon);

		GameObject* hpUI = new GameObject;

		mr = hpUI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Battle_HpUI_Material"));

		hpUI->GetComponent<Transform>()->SetScale(Vector3(1.3f, 0.2f, 1.f) * 0.17f);
		hpUI->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.15f, 0.f));
		hpUI->SetName(L"hpUI");
		hpUI->AddComponent<HpParentEffect>();
		hpUI->SetState(GameObject::eState::Dead);

		ratMon->AddChild(hpUI);

		GameObject* hpVal = new GameObject;

		mr = hpVal->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		if (hpIndex == 0)
			mr->SetMaterial(Resources::Find<Material>(L"Battle_HpVal_Material"));
		else if (hpIndex == 1)
			mr->SetMaterial(Resources::Find<Material>(L"Battle_HpVal_Material2"));
		else if (hpIndex == 2)
			mr->SetMaterial(Resources::Find<Material>(L"Battle_HpVal_Material3"));

		hpVal->AddComponent<HpValController>();

		hpVal->GetComponent<Transform>()->SetScale(Vector3(0.9f, 0.52f, 1.f));
		hpVal->GetComponent<Transform>()->SetPosition(Vector3(-0.015f, -0.02f, -0.1f));

		hpUI->AddChild(hpVal);
		hpVal->SetName(L"hpVal");


		if (index == 0)
			container->wave1.push_back(ratMon);
		else if (index == 1)
			container->wave2.push_back(ratMon);
		else if (index == 2)
			container->wave3.push_back(ratMon);
	}

}