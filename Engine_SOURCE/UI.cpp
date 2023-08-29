#include "UI.h"
#include "Script.h"
#include "GameObject.h"

namespace Jun {



	UI::UI()
		: Component(eComponentType::UI)
	{
	}

	UI::~UI()
	{
	}

	void UI::Initialize()
	{
	}

	void UI::Update()
	{
	}

	void UI::LateUpdate()
	{
	}

	void UI::Render()
	{
	}

	void UI::MouseOn()
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->MouseOn();
		}
	}
	void UI::MouseLbtnUp()
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->MouseLbtnUp();
		}
	}
	void UI::MouseLbtnDown()
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->MouseLbtnDown();
		}

		std::vector<GameObject*> childs = GetOwner()->GetChilds();

		for (GameObject* child : childs) {
			child->GetComponent<UI>()->MouseLbtnDown();
		}
	}
	void UI::MouseLbtnClicked()
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->MouseLbtnClicked();
		}
	}
}