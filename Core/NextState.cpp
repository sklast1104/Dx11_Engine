#include "NextState.h"
#include "SkeletonMecanim.h"
#include "MyTime.h"
#include "PlayerStateMachine.h"
#include "MonsterStateMachine.h"
#include "Object.h"

namespace Jun::PlayerState {

	using namespace Jun::object;

	void NextState::Enter()
	{
		owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);

		delay = 2.f;
		nextDelay = 4.5f;
		elapsedTime = 0.f;

		flag = true;
		fader = FindObjectOfType<Fader>();
		stageManager = FindObjectOfType<StageManager>();
	}

	void NextState::Update()
	{
		elapsedTime += Time::DeltaTime();

		if (delay < elapsedTime && flag) {
			
			flag = false;
			owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Run", true);
		}

		if (flag) return;

		Transform* tr = owner->GetComponent<Transform>();
		float speed = 1.5f;
		Vector3 movVec = dir * Time::DeltaTime() * speed;
		tr->SetPosition(tr->GetPosition() + movVec);

		if (elapsedTime > 4.f && faderFlag) {
			faderFlag = false;
			fader->StartFade();
		}

		if (elapsedTime > nextDelay) {
			PlayerStateMachine* machine = owner->GetComponent<PlayerStateMachine>();
			machine->SwitchState(machine->stateMap[L"StartState"].get());

			std::vector<GameObject*>& monsters = stageManager->GetNextStageMon();

			for (auto mon : monsters) {

				mon->SetState(GameObject::eState::Active);

				MonsterStateMachine* machine = mon->GetComponent<MonsterStateMachine>();
				machine->SwitchState(machine->stateMap[L"StartState"].get());
			}
		}
	}

	void NextState::Exit()
	{
		faderFlag = true;
	}

}