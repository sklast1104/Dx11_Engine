#pragma once
#include "Material.h"

namespace Jun::graphics {

	class FaderMaterial : public Material
	{
	public :

		FaderMaterial();
		virtual ~FaderMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

		float FadeVal;
	};
}



