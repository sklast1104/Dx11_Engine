#pragma once

#include "Engine.h"
#include "GraphicDevice_Dx11.h"
#include "Mesh.h"
#include "Shader.h"

using namespace Jun::math;

namespace Jun::renderer {

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern Jun::Mesh* mesh;

	extern ID3D11Buffer* triangleConstantBuffer;
	extern Jun::Shader* shader;

	extern ID3D11PixelShader* trianglePSShader;

	extern Vector4 offset;

	void Initialize();
	void Update();
	void Release();
}

