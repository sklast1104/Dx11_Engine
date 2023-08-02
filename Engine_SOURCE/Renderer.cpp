#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "RenderTexture.h"
#include "StructedBuffer.h"
#include "PaintShader.h"

namespace renderer
{
	using namespace Jun;
	using namespace Jun::graphics;

	Jun::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	//
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

	Jun::Camera* mainCamera = nullptr;
	std::vector<Jun::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = Jun::Resources::Find<Shader>(L"TriangleShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"SpriteShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"GridShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"DebugShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"SpriteAnimationShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"VideoShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = Jun::Resources::Find<Shader>(L"ParticleShader");
		Jun::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());

		{
			D3D11_SAMPLER_DESC sampDesc = {};
			sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
			sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampDesc.MinLOD = 0;
			sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
			GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Video].GetAddressOf());
			GetDevice()->BindSampler(eShaderStage::PS, 2, samplerState[(UINT)eSamplerType::Video].GetAddressOf());
		}

#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion


	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);


		vertexes.clear();
		indexes.clear();

		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());



		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eSRVType::None);
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		Jun::Resources::Insert(L"TriangleShader", shader);

		shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Jun::Resources::Insert(L"SpriteShader", shader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		Jun::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Jun::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		Jun::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<Shader> videoShader = std::make_shared<Shader>();
		videoShader->Create(eShaderStage::VS, L"VideoVS.hlsl", "main");
		videoShader->Create(eShaderStage::PS, L"VideoPS.hlsl", "main");
		Jun::Resources::Insert(L"VideoShader", videoShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Jun::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		Jun::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTitle() {

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<RenderTexture> renderTexture = std::make_shared<RenderTexture>();
		renderTexture->SetSlotNum(1);
		Resources::Insert(L"RenderTexture", renderTexture);

		std::shared_ptr<Shader> videoShader
			= Resources::Find<Shader>(L"VideoShader");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(videoShader);
		material->SetTexture(renderTexture);
		Resources::Insert(L"VideoMaterial", material);

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Title_Btns", L"..\\Resources\\Texture\\Title\\11-1.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Title_Btn_Material", material);

		texture = Resources::Load<Texture>(L"Title", L"..\\Resources\\Texture\\Title\\Title.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Title_Material", material);
	}

	void LoadMenuRes() {

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MenuBG", L"..\\Resources\\Texture\\Menu\\MainBg.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"MenuBG_Material", material);

		texture = Resources::Load<Texture>(L"Pecorinne", L"..\\Resources\\Texture\\Menu\\Pecorinne.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"Pecorinne_Material", material);

		texture = Resources::Load<Texture>(L"UI2", L"..\\Resources\\Texture\\Menu\\UI2.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"UI2_Material", material);

		texture = Resources::Load<Texture>(L"Bottom_nav_tex", L"..\\Resources\\Texture\\Menu\\Bottom_nav2.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"Bottom_nav_mat", material);
	}

	void LoadQuestRes() {

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"QuestBtns_Tex", L"..\\Resources\\Texture\\Quest\\QuestBtnsAlpha.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"QuestBtns_Material", material);

		texture = Resources::Load<Texture>(L"Quest_MainPanel_Tex", L"..\\Resources\\Texture\\Quest\\QuestPnal2.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"Quest_MainPanel_Material", material);

		texture = Resources::Load<Texture>(L"Quest_TopNav_Alpha_Tex", L"..\\Resources\\Texture\\Quest\\TopNav_Alpha.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"Quest_TopNav_Alpha_Material", material);
	}

	void LoadMapRes() {

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"QuestMap_WorldMap_Tex", L"..\\Resources\\Texture\\QuestMap\\WorldMap.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"QuestMap_WorldMap_Material", material);

		texture = Resources::Load<Texture>(L"Quest_QuestMapUI_Edit_Tex", L"..\\Resources\\Texture\\QuestMap\\QuestMapUI_Edit.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);

		Resources::Insert(L"Quest_QuestMapUI_Edit_Material", material);

	}

	void LoadBattleRes() {

		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Battle_BattleBG_Tex", L"..\\Resources\\Texture\\Battle\\BattleBGTex.png");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"Battle_BattleBG_Material", material);

		texture = Resources::Load<Texture>(L"Battle_BattleBaseUI_Tex", L"..\\Resources\\Texture\\Battle\\BattleBaseUI.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		
		Resources::Insert(L"Battle_BattleBaseUI_Material", material);

	}

	void LoadTexture() {
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Jun::Resources::Insert(L"PaintTexuture", uavTexture);
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");


		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", material);

		//texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		texture = Resources::Find<Texture>(L"PaintTexuture");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", material);

		shader
			= Resources::Find<Shader>(L"SpriteAnimationShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimaionMaterial", material);

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		shader
			= Resources::Find<Shader>(L"ParticleShader");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"ParticleMaterial", material);

		LoadTitle();
		LoadMenuRes();
		LoadQuestRes();
		LoadMapRes();
		LoadBattleRes();
		
	}

	void Initialize()
	{

		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->Bind(eShaderStage::VS, 13);
		lightsBuffer->Bind(eShaderStage::PS, 13);
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void Render()
	{
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}



