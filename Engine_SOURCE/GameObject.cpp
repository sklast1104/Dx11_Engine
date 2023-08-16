#include "GameObject.h"
#include "Renderer.h"
#include "GraphicDevice_Dx11.h"
#include "Transform.h"

namespace Jun
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}

		for (GameObject* child : childObjects) {
			delete child;
			child = nullptr;
		}

		childObjects.clear();
	}

	void GameObject::Initialize()
	{

	}

	void GameObject::Start()
	{
		if (mState == eState::Dead) return;

		for (Component* comp : mComponents)
		{
			comp->Start();
		}

		for (Script* script : mScripts)
		{
			script->Start();
		}

		for (GameObject* child : childObjects) {
			child->Start();
		}
	}

	void GameObject::Update()
	{
		if (mState == eState::Dead) return;

		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}

		for (GameObject* child : childObjects) {
			child->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		if (mState == eState::Dead) return;

		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}

		for (GameObject* child : childObjects) {
			child->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		if (mState == eState::Dead) return;

		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		for (Script* script : mScripts)
		{
			script->Render();
		}

		for (GameObject* child : childObjects) {
			child->Render();
		}
	}
	void GameObject::SetState(eState state)
	{
		mState = state;

		if (mState == eState::Dead) {
		
			for (auto child : childObjects) {
				child->SetState(state);
			}

		}
		else if (mState == eState::Active) {

			for (auto child : childObjects) {
				child->SetState(state);
			}

		}
	}
	void GameObject::AddChild(GameObject* _child)
	{
		if (mState == eState::Dead) _child->SetState(eState::Dead);

		_child->parent = this;
		_child->GetComponent<Transform>()->SetParent(GetComponent<Transform>());
		childObjects.push_back(_child);
	}
}
