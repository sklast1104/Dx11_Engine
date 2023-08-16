#pragma once
#include "Entity.h"
#include "Layer.h"
#include "GameObject.h"
#include <iostream>

namespace Jun {

	class Scene : public Entity {

	public :
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(eLayerType type, GameObject* gameObject);

		Layer* GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		std::vector<Layer*> GetLayers() { return mLayers; }

	private :
		std::vector<Layer*> mLayers;
	};
}



