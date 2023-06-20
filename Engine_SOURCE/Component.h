#pragma once
#include "Entity.h"

namespace Jun {

	using namespace Jun::enums;
	using namespace Jun::math;

	class GameObject;
	class Component : public Entity
	{
	public :
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private :
		const eComponentType mType;
		GameObject* mOwner;
	};

}



