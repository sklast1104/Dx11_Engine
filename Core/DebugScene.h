#pragma once

#include "Scene.h"

namespace Jun {

	class DebugScene : public Scene
	{
	public :
		DebugScene();
		virtual ~DebugScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}



