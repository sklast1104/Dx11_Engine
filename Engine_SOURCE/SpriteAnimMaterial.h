#pragma once
#include "Material.h"

namespace Jun::graphics {

	using namespace Jun::math;

	class SpriteAnimMaterial : public Material
	{
	public:

		SpriteAnimMaterial();
		virtual ~SpriteAnimMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

		Vector4 color;

	private:

	};

}



