#pragma once
#include "Resource.h"
#include "GraphicDevice_Dx11.h"

namespace Jun {

	using namespace graphics;

	class Mesh : public Resource
	{
	public :
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;


		bool CreateVertexBuffer(void* data, UINT Count);
		bool CreateIndexBuffer(void* data, UINT Count);

		void BindBuffer();
		void Render();
		void RenderInstanced(UINT startIndexLocation);

		UINT GetIndexCount() { return mIndexCount; }

	private :
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;

	};
}



