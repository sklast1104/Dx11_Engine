#include "Scene.h"

namespace Jun {

	Scene::Scene()
	{
		//mLayers.resize((int) Jun::enums::eLayerType::End);

		for (int i = 0; i < (int)Jun::enums::eLayerType::End; i++) {
			mLayers.push_back(new Layer);
		}
	}

	Scene::~Scene()
	{
		for (int i = 0; i < (int)Jun::enums::eLayerType::End; i++) {
			delete mLayers[i];
			mLayers[i] = nullptr;
		}

		mLayers.clear();
	}

	void Scene::Initialize()
	{
	}

	void Scene::Start()
	{
		for (Layer* layer : mLayers) {
			layer->Start();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers) {
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			layer->LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer* layer : mLayers)
		{
			layer->Destory();
		}
	}

	void Scene::OnEnter()
	{
		Start();
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(eLayerType type, GameObject* gameObject)
	{
		mLayers[(int)type]->AddGameObject(gameObject);
	}

}
