#pragma once

#include "Scene.h"

namespace Jun {

	class QuestMapScene : public Scene
	{
	public :
		QuestMapScene();
		virtual ~QuestMapScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}



