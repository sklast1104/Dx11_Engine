#pragma once

#include "Scene.h"

namespace Jun {

	class BattleScene2 : public Scene
	{
	public :
		BattleScene2();
		virtual ~BattleScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private :
		void InitMoster(Vector3 pos, GameObject* parent, int index, bool isActive, int hpIndex);
		int index = 3;

		std::vector<GameObject*> pps;
	};

}



