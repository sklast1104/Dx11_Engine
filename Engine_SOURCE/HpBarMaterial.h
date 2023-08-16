#pragma once
#include "Material.h"

namespace Jun::graphics {

	class HpBarMaterial : public Material
	{
	public :
		HpBarMaterial();
		virtual ~HpBarMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

		float hpPercent;
	};

}



