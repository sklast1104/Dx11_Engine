#pragma once

#include "Scene.h"

namespace Jun {

	class QuestScene : public Scene
	{
	public :
		QuestScene();
		virtual ~QuestScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}



