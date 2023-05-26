#include "Renderer.h"

namespace Jun::renderer {

	Vertex vertexes[500] = {};

	// Input Layout (Á¤Á¡ Á¤º¸)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	ID3DBlob* trianglePSBlob = nullptr;

	// Pixel Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	int vertexCount = 0;

	void SetupState() {

	}

	void LoadBuffer() {
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * vertexCount;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		Jun::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
	}

	void LoadShader() {
		Jun::graphics::GetDevice()->CreateShader();
	}

	void MakeSquare(Vector2 offset, Vector2 scale) {
		vertexes[vertexCount].pos = Vector3(-0.5f * scale.x + offset.x, 0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 1].pos = Vector3(0.5f * scale.x + offset.x, -0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount + 1].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[vertexCount + 2].pos = Vector3(-0.5f * scale.x + offset.x, -0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount + 2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 3].pos = Vector3(-0.5f * scale.x + offset.x, 0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount + 3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 4].pos = Vector3(0.5f * scale.x + offset.x, 0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount + 4].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 5].pos = Vector3(0.5f * scale.x + offset.x, -0.5f * scale.y + offset.y, 0.0f);
		vertexes[vertexCount + 5].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexCount += 6;
	}

	void MakeDiamond(Vector2 offset, Vector2 scale) {
		// »ï°¢Çü 1
		vertexes[vertexCount].pos = Vector3(offset.x, offset.y + 0.5f * scale.y, 0.0f);
		vertexes[vertexCount].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 1].pos = Vector3(offset.x - 0.5f * scale.x, offset.y, 0.0f);
		vertexes[vertexCount + 1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 2].pos = Vector3(offset.x, offset.y - 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		// »ï°¢Çü 2
		vertexes[vertexCount + 3].pos = Vector3(offset.x, offset.y + 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 4].pos = Vector3(offset.x + 0.5f * scale.x, offset.y, 0.0f);
		vertexes[vertexCount + 4].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[vertexCount + 5].pos = Vector3(offset.x, offset.y - 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		// »ï°¢Çü 3
		vertexes[vertexCount + 6].pos = Vector3(offset.x, offset.y + 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 6].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 7].pos = Vector3(offset.x + 0.5f * scale.x, offset.y, 0.0f);
		vertexes[vertexCount + 7].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 8].pos = Vector3(offset.x, offset.y + 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 8].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		// »ï°¢Çü 4
		vertexes[vertexCount + 9].pos = Vector3(offset.x, offset.y - 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 9].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 10].pos = Vector3(offset.x - 0.5f * scale.x, offset.y, 0.0f);
		vertexes[vertexCount + 10].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[vertexCount + 11].pos = Vector3(offset.x, offset.y + 0.5f * scale.y, 0.0f);
		vertexes[vertexCount + 11].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexCount += 12;
	}

	void MakeCircle(Vector2 offset, float radius, int numSlices) {
		const float angleIncrement = 2.0f * 3.1415926535 / static_cast<float>(numSlices);

		for (int i = 0; i < numSlices; ++i) {
			float angle = angleIncrement * static_cast<float>(i);
			float x1 = offset.x + radius * std::cos(angle);
			float y1 = offset.y + radius * std::sin(angle);
			float x2 = offset.x + radius * std::cos(angle + angleIncrement);
			float y2 = offset.y + radius * std::sin(angle + angleIncrement);

			vertexes[vertexCount].pos = Vector3(offset.x, offset.y, 0.0f);
			vertexes[vertexCount].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

			vertexes[vertexCount + 1].pos = Vector3(x2, y2, 0.0f);
			vertexes[vertexCount + 1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

			vertexes[vertexCount + 2].pos = Vector3(x1, y1, 0.0f);
			vertexes[vertexCount + 2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

			vertexCount += 3;
		}
	}

	void Initialize() {

		MakeDiamond(Vector2(-0.5f, 0.0f), Vector2(0.3f, 0.3f));
		MakeSquare(Vector2(0.f, 0.f), Vector2(0.2f, 0.2f));
		MakeCircle(Vector2(0.7f, 0.0f), 0.2f, 20);

		SetupState();
		LoadBuffer();
		LoadShader();
	}

	
}
