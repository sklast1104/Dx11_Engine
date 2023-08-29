#include "MonsterBattleManager.h"
#include "Object.h"
#include "PlayerStateMachine.h"

namespace Jun {

	using namespace Jun::object;
	using namespace Jun::PlayerState;

	void MonsterBattleManager::Initialize()
	{
	}

	void MonsterBattleManager::Start()
	{
	}

	void MonsterBattleManager::Update()
	{
	}

	void MonsterBattleManager::LateUpdate()
	{
	}

	void MonsterBattleManager::Render()
	{
	}

	GameObject* MonsterBattleManager::FindTarget()
	{
		 std::vector<PlayerStateMachine*> heros = FindObjectsOfType<PlayerStateMachine>();

		 GameObject* closeGo = nullptr;
		 float closestDist = 100.f;

		 for (auto hero : heros) {

			 GameObject* go = hero->GetOwner();
			 Transform* tr = go->GetComponent<Transform>();
			 float dist = tr->GetPosition().x;

			 if (dist < closestDist) {
				 closestDist = dist;
				 closeGo = tr->GetOwner();
			 }

		 }

		return closeGo;
	}

}