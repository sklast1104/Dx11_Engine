#pragma once

#include "Scene.h"

namespace Jun {

	class BattleScene : public Scene
	{
	public :
		BattleScene();
		virtual ~BattleScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};

}



