#include "ConstantBuffer.h"
#include "GraphicDevice_Dx11.h"

namespace Jun::graphics {

	ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		Jun::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}
	void ConstantBuffer::SetData(void* data)
	{
		Jun::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}
	void ConstantBuffer::Bind(eShaderStage stage)
	{
		Jun::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}
}



