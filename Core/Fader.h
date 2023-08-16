#pragma once
#include "Script.h"
#include "FaderMaterial.h"

namespace Jun {

	class Fader : public Script
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

		FaderMaterial* mt;
	};


}


