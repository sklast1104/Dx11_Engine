#pragma once
#include "Script.h"

namespace Jun {

	namespace graphics {
		class SpriteAnimMaterial;
	}

	class DieEffect : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Jun::graphics::SpriteAnimMaterial* material;

		void PlayEffect();

	private :

		bool flag;
		float delay;
		float elapsedTime;

	};
}


