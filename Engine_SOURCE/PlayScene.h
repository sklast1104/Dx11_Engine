#pragma once
#include "Scene.h"

namespace Jun {

	class PlayScene : public Scene
	{
	public :
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private :


	};

}


