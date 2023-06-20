#pragma once
#include "GameObject.h"

namespace Jun {

	class Layer
	{
	public :
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
	private :
		std::vector<GameObject*> mGameObjects;

	};

}



