#pragma once
#include "Entity.h"
#include "Layer.h"

namespace Jun {

	class Scene : public Entity {

	public :
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(eLayerType type, GameObject* gameObject);

	private :
		std::vector<Layer> mLayers;

	};
}



