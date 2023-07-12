#include "guiEditor.h"
#include "Mesh.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Renderer.h"


#include "GridScript.h"

namespace gui
{
	using namespace Jun::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Jun::Mesh> mesh
			= Jun::Resources::Find<Jun::Mesh>(L"DebugRect");
		std::shared_ptr<Jun::Material> material
			= Jun::Resources::Find<Jun::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Jun::Transform>();
		Jun::MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Jun::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);

		{
			mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();

			Jun::MeshRenderer* mr
				= mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<Jun::MeshRenderer>();

			std::shared_ptr<Jun::Mesh> mesh
				= Jun::Resources::Find<Jun::Mesh>(L"DebugCircle");
			std::shared_ptr<Jun::Material> material
				= Jun::Resources::Find<Jun::Material>(L"DebugMaterial");

			mr->SetMaterial(material);
			mr->SetMesh(mesh);
		}


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<Jun::MeshRenderer>();
		mr->SetMesh(Jun::Resources::Find<Jun::Mesh>(L"RectMesh"));
		mr->SetMaterial(Jun::Resources::Find<Jun::Material>(L"GridMaterial"));
		Jun::GridScript* gridSc = grid->AddComponent<Jun::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)ya::graphics::eDSType::Less];
		//ya::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const Jun::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}

	}

	void Editor::DebugRender(const Jun::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		Jun::Transform* tr = debugObj->GetComponent<Jun::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*ya::MeshRenderer * mr
			= debugObj->GetComponent<ya::MeshRenderer>();*/
			// main camera
		Jun::Camera* mainCamara = renderer::mainCamera;

		Jun::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		Jun::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());

		debugObj->Render();
	}
}
