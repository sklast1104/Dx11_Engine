#include "PostProcess.h"
#include "Renderer.h"
#include "Application.h"

extern Jun::Application application;

namespace Jun {

	PostProcess::PostProcess()
		: Component(eComponentType::PostProcess)
		, slotNum{51}
	{
	}
	PostProcess::~PostProcess()
	{
	}
	void PostProcess::Initialize()
	{
		for (int i = 0; i < 8; i++) {
			std::shared_ptr<Texture> tex = std::make_shared<Texture>();
			tex->Create(application.GetWidth(), application.GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
			tex->BindShaderResource(eShaderStage::PS, 60 + i);

			destTextures.push_back(tex);
		}

		destTexture = std::make_shared<Texture>();
		destTexture->Create(application.GetWidth(), application.GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
		destTexture->BindShaderResource(eShaderStage::PS, 60);

		D3D11_TEXTURE2D_DESC txtDesc;
		ZeroMemory(&txtDesc, sizeof(txtDesc));
		txtDesc.Width = application.GetWidth();
		txtDesc.Height = application.GetHeight();
		txtDesc.MipLevels = txtDesc.ArraySize = 1;
		txtDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //  이미지 처리용도
		txtDesc.SampleDesc.Count = 1;
		txtDesc.Usage = D3D11_USAGE_DEFAULT;
		txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE |
			D3D11_BIND_RENDER_TARGET |
			D3D11_BIND_UNORDERED_ACCESS;
		txtDesc.MiscFlags = 0;
		txtDesc.CPUAccessFlags = 0;

		D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
		viewDesc.Format = txtDesc.Format;
		viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipSlice = 0;

		D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
		tSRVDesc.Format = txtDesc.Format;
		tSRVDesc.Texture2D.MipLevels = 1;
		tSRVDesc.Texture2D.MostDetailedMip = 0;
		tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

		GetDevice()->CreateTexture2D(&txtDesc, NULL, texture.GetAddressOf());
		GetDevice()->CreateRenderTargetView(texture.Get(), &viewDesc,
			m_renderTargetView.GetAddressOf());
		GetDevice()->CreateShaderResourceView(texture.Get(), &tSRVDesc,
			m_shaderResourceView.GetAddressOf());

		this->SetRenderTargets({ m_renderTargetView });


	}
	void PostProcess::Update()
	{
	}
	void PostProcess::LateUpdate()
	{
	}
	void PostProcess::Render()
	{
		//assert(m_shaderResources.size() > 0);
		//assert(m_renderTargets.size() > 0);

		GetDevice()->GetID3D11DeviceContext()->OMSetRenderTargets(UINT(m_renderTargets.size()),
			m_renderTargets.data(), nullptr);

		for (int i = 0; i < inputTextures.size(); i++) {
			GetDevice()->CopyResource(destTextures[i]->GetTexture().Get(), inputTextures[i]->GetTexture().Get());
			destTextures[i]->BindShaderResource(eShaderStage::PS, 60 + i);
		}


		//GetDevice()->CopyResource(destTexture->GetTexture().Get(), inputTexture->GetTexture().Get());

		//destTexture->BindShaderResource(eShaderStage::PS, 60);

		//GetDevice()->GetID3D11DeviceContext()->PSSetShaderResources(60, UINT(m_shaderResources.size()), m_shaderResources.data());
		//destTexture->BindShaderResource(eShaderStage::PS, 60);
	}
	void PostProcess::CopyRenderTarget(int slotNum)
	{
		std::shared_ptr<Texture> renderTarget = renderer::renderTarget;

		//GetDevice()->CopyResource(postProcessTexture->GetTexture().Get()
		//	, renderTarget->GetTexture().Get());

		renderTarget->BindShaderResource(eShaderStage::PS, slotNum);
	}
}