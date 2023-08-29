#pragma once
#include "Material.h"

namespace Jun::graphics {

	class SwordTrailMaterial : public Material
	{
	public :

		SwordTrailMaterial();
		virtual ~SwordTrailMaterial();

		virtual void Binds() override;
		virtual void Clear() override;

		void BindConstantBuffer();

	private :

	};


}


