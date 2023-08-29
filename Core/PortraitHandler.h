#pragma once
#include "Script.h"

namespace Jun {

	class PortraitHandler : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void MouseLbtnDown() override;

	private :
		class GameObject* video;
		float elapsed;
		float delay;
		bool flag;
	};

}



