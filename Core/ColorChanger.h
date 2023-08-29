#pragma once
#include "Script.h"

namespace Jun {

	namespace graphics {
		class SpriteAnimMaterial;
	}

	class ColorChanger : public Script
	{
	public :
		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Jun::graphics::SpriteAnimMaterial* material;

		void AttackedEffect();

	private :
		bool flag;
		float delay;
		float elapsedTime;
	};
}



