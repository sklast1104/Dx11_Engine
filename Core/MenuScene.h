#pragma once

#include "Scene.h"

namespace Jun {

	class MenuScene : public Scene
	{
	public :
		MenuScene();
		virtual ~MenuScene();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};

}



