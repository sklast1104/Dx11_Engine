#pragma once
#include "Script.h"

namespace Jun {

	class MonsterBattleManager : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		class GameObject* FindTarget();

	private :

	};

}



