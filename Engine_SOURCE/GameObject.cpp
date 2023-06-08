#include "GameObject.h"
#include "Renderer.h"
#include "GraphicDevice_Dx11.h"

namespace Jun{

	GameObject::GameObject()
		: mState(eState::Active)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render()
	{
		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}
