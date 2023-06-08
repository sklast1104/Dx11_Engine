#include "Scene.h"

namespace Jun {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
	}

	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Render();
		}
	}

}