#pragma once
#include "Script.h"

namespace Jun {

	class StageManager : public Script
	{

	public :

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void ResetStageConfig() { flag = true; }
		void NextChecker();

		std::vector<GameObject*>& GetCurrentStageMon();
		std::vector<GameObject*>& GetNextStageMon();

	private :

		bool flag;

		void CheckAlive(std::vector<GameObject*>& mons);

		class MonsterContainer* container;
		int stageIndex;
	};

}



