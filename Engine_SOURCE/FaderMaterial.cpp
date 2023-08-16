#include "FaderMaterial.h"
#include "Renderer.h"

namespace Jun::graphics {
	FaderMaterial::FaderMaterial()
		: FadeVal{0.0f}
	{
	}
	FaderMaterial::~FaderMaterial()
	{
	}
	void FaderMaterial::Binds()
	{
		Material::Binds();
		BindConstantBuffer();
	}

	void FaderMaterial::Clear()
	{
		Material::Clear();
	}

	void FaderMaterial::BindConstantBuffer()
	{
		renderer::FaderCB faderCB = {};
		faderCB.fadeVal = FadeVal;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Fader];
		cb->SetData(&faderCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}