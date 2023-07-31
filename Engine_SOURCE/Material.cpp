#include "Material.h"

namespace Jun::graphics {

	Material::Material()
		: Resource(Jun::enums::eResourceType::Material)
		, mShader{nullptr}
		, mTexture{nullptr}
		, mMode(eRenderingMode::Opaque)
	{
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{
		if (mTexture)
			mTexture->BindShaderResource(eShaderStage::PS, mTexture->GetSlotNum());

		if (mShader)
			mShader->Binds();
	}

	void Material::Clear()
	{
		mTexture->Clear();
	}

}