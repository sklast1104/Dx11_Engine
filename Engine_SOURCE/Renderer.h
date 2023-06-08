#pragma once

#include "Engine.h"
#include "GraphicDevice_Dx11.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"

using namespace Jun::math;

namespace Jun::renderer {

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern Jun::Mesh* mesh;

	extern Jun::Shader* shader;
	extern Jun::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}

