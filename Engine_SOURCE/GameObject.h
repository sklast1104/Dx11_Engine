#pragma once
#include "Entity.h"
#include "Component.h"
#include "Script.h"

namespace Jun
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();



		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		const std::vector<T*> GetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}

		template <typename T>
		T* GetComponentInChild() {

			T* component = GetComponent<T>();

			if (component) return component;

			for (GameObject* child : childObjects) {
				component = child->GetComponentInChild<T>();

				if (component) return component;
			}

			return nullptr;
		}

		template <typename T>
		const std::vector<T*> GetComponentsInChild() {

			std::vector<T*> comps;

			T* component;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (Script* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (GameObject* child : childObjects) {

				std::vector<T*> childCompos = child->GetComponentsInChild<T>();

				for (T* item : childCompos) {
					comps.push_back(item);
				}
			}

			return comps;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			Component* buff
				= dynamic_cast<Component*>(comp);
			Script* script
				= dynamic_cast<Script*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->SetOwner(this);
			comp->Initialize();

			return comp;
		}

		void SetState(eState state);
		eState GetState() { return mState; }

		// 메모리 이슈있을수도 있음 체크
		void AddChild(GameObject* _child);

		std::vector<GameObject*> GetChilds() { return childObjects; }
		GameObject* GetParent() { return parent; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;

		GameObject* parent;
		std::vector<GameObject*> childObjects;
	};
}
