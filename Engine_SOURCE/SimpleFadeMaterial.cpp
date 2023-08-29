#include "SimpleFadeMaterial.h"
#include "Renderer.h"

namespace Jun::graphics {

	SimpleFadeMaterial::SimpleFadeMaterial()
		: fadeVal{1.f}
	{
	}

	SimpleFadeMaterial::~SimpleFadeMaterial()
	{
	}

	void SimpleFadeMaterial::Binds()
	{
		Material::Binds();
		BindConstantBuffer();
	}

	void SimpleFadeMaterial::Clear()
	{
		Material::Clear();
	}

	void SimpleFadeMaterial::BindConstantBuffer()
	{
		renderer::FaderCB faderCB = {};
		faderCB.fadeVal = fadeVal;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Fader];
		cb->SetData(&faderCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

}