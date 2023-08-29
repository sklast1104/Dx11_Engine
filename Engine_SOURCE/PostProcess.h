#pragma once
#include "Component.h"
#include "Texture.h"

namespace Jun {

	using namespace Jun::graphics;
	using namespace Microsoft::WRL;

	class PostProcess : public Component
	{
	public :

		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		PostProcess();
		~PostProcess();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void CopyRenderTarget(int slotNum);

		void SetShaderResources(
			const std::vector<ComPtr<ID3D11ShaderResourceView>>& resources) {

			m_shaderResources.clear();
			for (const auto& res : resources) {
				m_shaderResources.push_back(res.Get());
			}
		}

		void SetRenderTargets(
			const std::vector<ComPtr<ID3D11RenderTargetView>>& targets) {

			m_renderTargets.clear();
			for (const auto& tar : targets) {
				m_renderTargets.push_back(tar.Get());
			}
		}

		void SetInputTexture(std::shared_ptr<Texture> _tex) {
			inputTexture = _tex;
		}

		std::shared_ptr<Texture> GetDestTex() {
			return destTexture;
		}

		std::shared_ptr<Texture> GetDestTex(int index) {
			return destTextures[index];
		}

		void SetInputTextures(const std::vector<std::shared_ptr<Texture>>& targets) {

			inputTextures.clear();

			for (const auto& tar : targets) {
				inputTextures.push_back(tar);
			}
		}

	private :
		
		ComPtr<ID3D11Texture2D> texture;
		int slotNum;

		std::vector<ID3D11ShaderResourceView*> m_shaderResources;
		std::vector<ID3D11RenderTargetView*> m_renderTargets;

		std::vector<std::shared_ptr<Texture>> inputTextures;
		std::vector<std::shared_ptr<Texture>> destTextures;
		std::shared_ptr<Texture> destTexture;
		std::shared_ptr<Texture> inputTexture;
	};

}


