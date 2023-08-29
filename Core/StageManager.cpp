#include "StageManager.h"
#include "Object.h"
#include "MonsterStateMachine.h"
#include "PlayerStateMachine.h"
#include "Health.h"
#include "MonsterContainer.h"

namespace Jun {

	using namespace Jun::object;
	using namespace Jun::PlayerState;

	void StageManager::Initialize()
	{
		flag = true;

		container = FindObjectOfType<MonsterContainer>();
		stageIndex = 0;
	}

	void StageManager::Update()
	{
		NextChecker();
	}

	void StageManager::LateUpdate()
	{
	}

	void StageManager::Render()
	{
	}

	void StageManager::NextChecker()
	{
		if (stageIndex == 0) {

			auto monsters = container->wave1;

			CheckAlive(monsters);

		}
		else if (stageIndex == 1) {

			auto monsters = container->wave2;

			CheckAlive(monsters);

		}
		else if (stageIndex == 2) {

			auto monsters = container->wave3;

			CheckAlive(monsters);

		}
	}

	std::vector<GameObject*>& StageManager::GetCurrentStageMon()
	{
		if (stageIndex == 0) {
			return container->wave1;
		}
		else if (stageIndex == 1) {

			return container->wave2;

		}else if (stageIndex == 2) {

			return container->wave3;

		}
		else {
			//assert(false);
			return container->wave1;
		}
	}

	std::vector<GameObject*>& StageManager::GetNextStageMon()
	{
		if (stageIndex - 1 == 0) {
			return container->wave2;

		}
		else if (stageIndex - 1 == 1) {

			return container->wave3;

		}
		else {
			//assert(false);
			return container->wave3;
		}
	}

	void StageManager::CheckAlive(std::vector<GameObject*>& mons)
	{
		for (auto mon : mons) {

			if (mon->GetComponent<Health>()->IsAlive()) {
				return;
			}
		}

		if (flag) {
			flag = false;
			stageIndex += 1;

			auto players = FindObjectsOfType<PlayerStateMachine>();

			for (auto player : players) {
				player->SwitchState(player->stateMap[L"NextState"].get());
			}
		}
	}

}