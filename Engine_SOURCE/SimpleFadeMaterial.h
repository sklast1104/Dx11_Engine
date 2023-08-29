#pragma once
#include "Material.h"

namespace Jun::graphics {

	class SimpleFadeMaterial : public Material
	{
	public :

		float fadeVal;

		SimpleFadeMaterial();
		virtual ~SimpleFadeMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

	};

}



