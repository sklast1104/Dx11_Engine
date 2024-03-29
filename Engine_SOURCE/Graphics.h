#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "Enums.h"
#include "MyMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				2
#define CBSLOT_ANIMATION2D		3
#define CBSLOT_PARTICLE			4
#define CBSLOT_NOISE			5

#define CBSLOT_SPRITE 6
#define CBSLOT_FADER 7
//#define CBSLOT_PARTICLE			1

namespace Jun::graphics {
	enum class eShaderStage {
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End,
	};

	enum class eCBType {
		Transform,
		Material,
		Grid,
		Animator,
		Particle,
		Noise,
		Sprite,
		Fader,
		End,
	};

	enum class eSamplerType {
		Point,
		Anisotropic,
		Video,
		End,
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		PostProcess,
		End,
	};

	enum class eViewType
	{
		None,
		SRV,
		UAV,
		End,
	};

	struct GpuBuffer {

		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}

		virtual ~GpuBuffer() = default;

	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
	};

	struct LightAttribute
	{
		math::Vector4 color;
		math::Vector4 position;
		math::Vector4 direction;

		enums::eLightType type;
		float radius;
		float angle;
		int pad;
	};

	struct Particle
	{
		math::Vector4 position;
		math::Vector4 direction;

		float endTime;
		float time;
		float speed;
		UINT active;
	};

	struct ParticleShared
	{
		UINT sharedActiveCount;
	};
}

