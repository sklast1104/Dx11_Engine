#pragma once
#include "Script.h"

namespace Jun {

	class MonsterContainer : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		std::vector<GameObject*> wave1;
		std::vector<GameObject*> wave2;
		std::vector<GameObject*> wave3;
	};

}



