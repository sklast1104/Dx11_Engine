#include "SpriteAnimMaterial.h"
#include "Renderer.h"

namespace Jun::graphics {

	SpriteAnimMaterial::SpriteAnimMaterial()
		: color{1.f,1.f,1.f,1.f}
	{
	}

	SpriteAnimMaterial::~SpriteAnimMaterial()
	{
	}

	void SpriteAnimMaterial::Binds()
	{
		Material::Binds();
		BindConstantBuffer();
	}

	void SpriteAnimMaterial::Clear()
	{
		Material::Clear();
	}

	void SpriteAnimMaterial::BindConstantBuffer()
	{
		renderer::SpriteCB spriteData = {};
		spriteData.spriteColor = color;
		spriteData.hpPercent = 1.f;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Sprite];
		cb->SetData(&spriteData);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}