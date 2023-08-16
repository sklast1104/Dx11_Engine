#pragma once
#include "GameObject.h"

namespace Jun {

	class Layer
	{
	public :
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}
	private :
		std::vector<GameObject*> mGameObjects;

	};

}



