#include "BgEffectMaterial.h"
#include "Renderer.h"
#include "MyTime.h"

#include <iostream>

namespace Jun::graphics {



	BgEffectMaterial::BgEffectMaterial()
	{
		elapsed = 0.f;
	}

	BgEffectMaterial::~BgEffectMaterial()
	{
	}

	void BgEffectMaterial::Binds()
	{
		Material::Binds();
		BindConstantBuffer();
	}

	void BgEffectMaterial::Clear()
	{
		Material::Clear();
	}

	void BgEffectMaterial::BindConstantBuffer()
	{
		elapsed += Time::DeltaTime();

		renderer::SpriteCB spriteCb = {};
		
		spriteCb.delta = elapsed;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Sprite];
		cb->SetData(&spriteCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}