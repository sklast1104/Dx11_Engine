#pragma once
#include "Graphics.h"

namespace Jun::graphics {

	class ConstantBuffer : public GpuBuffer
	{
	public :
		ConstantBuffer(const eCBType type);
		~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

	private :
		const eCBType mType;
	};

}



