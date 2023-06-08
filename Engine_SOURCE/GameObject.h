#pragma once
#include "Entity.h"
#include "Component.h"

namespace Jun {

	class GameObject : public Entity
	{
	public :
		enum eState {
			Active,
			Paused,
			Dead
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private :
		eState mState;
	};
}



