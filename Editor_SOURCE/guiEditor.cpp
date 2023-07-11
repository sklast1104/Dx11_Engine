#include "guiEditor.h"
#include "Mesh.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GridScript.h"
#include "Renderer.h"

namespace gui
{
	using namespace Jun::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugOjbects = {};

	void Editor::Initialize()
	{
		mDebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<Jun::Mesh> mesh
			= Jun::Resources::Find<Jun::Mesh>(L"DebugRect");
		std::shared_ptr<Jun::Material> material
			= Jun::Resources::Find<Jun::Material>(L"DebugMaterial");

		mDebugOjbects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<Jun::Transform>();
		Jun::MeshRenderer* mr
			= mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<Jun::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


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
	}

	void Editor::DebugRender(const Jun::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugOjbects[(UINT)mesh.type];

		// ��ġ ũ�� ȸ�� ������ �޾ƿͼ�
		// �ش� ���ӿ�����Ʈ���� �׷��ָ�ȴ�.



		debugObj->Render();
	}
}
