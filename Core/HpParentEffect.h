#pragma once
#include "Script.h"

namespace Jun {

	class HpParentEffect : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void PlayEffect();

	private :

		bool flag;
		float delay;
		float elapsedTime;

	};

}



