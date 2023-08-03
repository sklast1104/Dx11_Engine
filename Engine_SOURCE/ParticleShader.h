#pragma once
#include "ComputeShader.h"
#include "StructedBuffer.h"

namespace Jun::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetParticleBuffer(StructedBuffer* particleBuffer);

	private:
		StructedBuffer* mParticleBuffer;

	};
}
