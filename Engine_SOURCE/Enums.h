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
		Camera,
		End,
	};

	enum class eLayerType {
		Grid,
		Player,
		Monster,
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
}