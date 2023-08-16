#include "HpBarMaterial.h"
#include "Renderer.h"

namespace Jun::graphics {

	HpBarMaterial::HpBarMaterial()
		: hpPercent{0.5f}
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