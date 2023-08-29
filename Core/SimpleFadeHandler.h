#pragma once
#include "Script.h"
#include "SimpleFadeMaterial.h"

namespace Jun {

	class SimpleFadeHandler : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void StartFade();

	private :

		float speed;
		float delay;

		float elapsedTime;
		bool flag;
		bool flag2;

		SimpleFadeMaterial* mt;

	};

}



