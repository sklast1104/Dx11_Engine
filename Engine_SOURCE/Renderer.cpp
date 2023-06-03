#include "Renderer.h"

#include "Input.h"

namespace Jun::renderer {

	Vertex vertexes[3] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	Jun::Mesh* mesh = nullptr;

	ID3D11Buffer* triangleConstantBuffer = nullptr;

	Jun::Shader* shader = nullptr;

	// Pixel Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	Vector4 offset = Vector4(0.f, 0.f, 0.f, 0.f);

	void SetupState() {

	}

	void LoadBuffer() {

		// Vertex Buffer
		mesh = new Jun::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
			
		// Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		Jun::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		Jun::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		Jun::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
	}

	void LoadShader() {
		
		shader = new Jun::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize() {

		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}
	void Update()
	{
		if(Input::GetKeyDown(eKeyCode::W)) {
			offset += Vector4(0.0f, 0.1f, 0.0f, 0.0f);

			Jun::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &offset, sizeof(Vector4));
			Jun::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		}

		if (Input::GetKeyDown(eKeyCode::S)) {
			offset += Vector4(0.0f, -0.1f, 0.0f, 0.0f);

			Jun::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &offset, sizeof(Vector4));
			Jun::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		}

		if (Input::GetKeyDown(eKeyCode::A)) {
			offset += Vector4(-0.1f, 0.0f, 0.0f, 0.0f);

			Jun::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &offset, sizeof(Vector4));
			Jun::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		}

		if (Input::GetKeyDown(eKeyCode::D)) {
			offset += Vector4(0.1f, 0.0f, 0.0f, 0.0f);

			Jun::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &offset, sizeof(Vector4));
			Jun::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
		}
	}
	void Release()
	{
		if (triangleLayout != nullptr)
			triangleLayout->Release();

		if (triangleConstantBuffer != nullptr)
			triangleConstantBuffer->Release();

		if (trianglePSShader != nullptr)
			trianglePSShader->Release();
	}
}
