#include "BattleManager.h"
#include "Object.h"
#include "MonsterStateMachine.h"
#include "Transform.h"
#include "StageManager.h"
#include "BattleManager.h"

namespace Jun {

	using namespace Jun::object;

	BattleManager::BattleManager()
		: xLimit{0.f}
		, xDist{0.f}
		, machine{nullptr}
		, isMove{false}
		, isNext{false}
	{
	}

	BattleManager::~BattleManager()
	{
	}

	void BattleManager::Initialize()
	{
		
	}

	void BattleManager::Start()
	{
		stageManager = FindObjectOfType<StageManager>();
	}

	void BattleManager::Update()
	{
		GameObject* shortest = FindTarget();

		if (shortest == nullptr) {

			isNext = true;

			return;
		}

		float monPosX = shortest->GetComponent<Transform>()->GetPosition().x;
		float myPosX = GetOwner()->GetComponent<Transform>()->GetPosition().x;

		float abDist = abs(monPosX - myPosX);

		if (abDist < xLimit) {
			// OnStop
			isMove = false;
		}
		else {
			// OnMove
			isMove = true;
		}
	}

	void BattleManager::LateUpdate()
	{
	}

	void BattleManager::Render()
	{
	}

	GameObject* BattleManager::FindTarget()
	{
		GameObject* closeGo = nullptr;
		float closestDist = 100.f;

		//auto monsters = FindObjectsOfType<MonsterStateMachine>();
		stageManager = FindObjectOfType<StageManager>();
		std::vector<GameObject*> monsters = stageManager->GetCurrentStageMon();

		for (auto mon : monsters) {

			Transform* trans = mon->GetComponent<Transform>();
			GameObject* monster = trans->GetOwner();
			float dist = trans->GetPosition().x;

			if (dist < closestDist && monster->GetState() == GameObject::eState::Active) {
				closestDist = dist;
				closeGo = trans->GetOwner();
			}
		}

		return closeGo;
	}

	bool BattleManager::IsMove()
	{
		return isMove;
	}

}