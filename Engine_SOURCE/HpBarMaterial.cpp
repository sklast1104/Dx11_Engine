#include "HpBarMaterial.h"
#include "Renderer.h"
#include <iostream>

namespace Jun::graphics {

	HpBarMaterial::HpBarMaterial()
		: hpPercent{1.f}
	{
	}

	HpBarMaterial::~HpBarMaterial()
	{
	}

	void HpBarMaterial::Binds()
	{
		Material::Binds();
		BindConstantBuffer();
	}

	void HpBarMaterial::Clear()
	{
		Material::Clear();
	}

	void HpBarMaterial::BindConstantBuffer()
	{
		renderer::SpriteCB spriteCB = {};
		spriteCB.hpPercent = hpPercent;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Sprite];
		cb->SetData(&spriteCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}