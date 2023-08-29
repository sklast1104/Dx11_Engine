#pragma once

namespace Jun::enums {

	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		VideoPlayer,
		Animator,
		Script,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		UI,
		PostProcess,
		End,
	};

	enum class eLayerType {
		Grid,
		Default,
		Logic,
		Player,
		Monster,
		Light,
		UI,
		Camera,
		End = 16,
	};

	enum class eResourceType {
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}