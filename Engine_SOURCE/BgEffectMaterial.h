#pragma once
#include "Material.h"

namespace Jun::graphics {

	class BgEffectMaterial : public Material
	{
	public :

		BgEffectMaterial();
		virtual ~BgEffectMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

	private :
		float elapsed;

	};


}


