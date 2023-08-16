#pragma once
#include "Script.h"

namespace Jun {

	class BattleManager : public Script
	{
	public :
		BattleManager();
		~BattleManager();

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		class GameObject* FindTarget();
		bool IsMove();
		bool IsNext() { return isNext; }

		float xLimit;
		class PlayerStateMachine* machine;



	private :
		float xDist;
		bool isMove;
		bool isNext;
		class StageManager* stageManager;
	};
}



