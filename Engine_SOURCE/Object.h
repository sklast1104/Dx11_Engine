#pragma once
#include "Layer.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"


namespace Jun::object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);
		tr->SetScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(Jun::GameObject::eState::Dead);
	}

	template <typename T>
	static __forceinline T* FindObjectOfType()
	{
		Scene* scene = SceneManager::GetActiveScene();
		
		std::vector<Layer*> mLayers = scene->GetLayers();

		for (Layer* layer : mLayers)
		{
			auto gameObjs = layer->GetGameObjects();
			for (GameObject* obj : gameObjs)
			{
				T* buff = obj->GetComponent<T>();
				if (buff != nullptr)
					return buff;

				for (GameObject* child : obj->GetChilds()) {
					T* buff = child->GetComponent<T>();
					if (buff != nullptr)
						return buff;
				}
			}
		}

		return nullptr;
	}

	template <typename T>
	static __forceinline std::vector<T*> FindObjectsOfType() {

		Scene* scene = SceneManager::GetActiveScene();

		std::vector<Layer*> mLayers = scene->GetLayers();

		std::vector<T*> objs;

		for (Layer* layer : mLayers)
		{
			auto gameObjs = layer->GetGameObjects();
			for (GameObject* obj : gameObjs)
			{
				T* buff = obj->GetComponent<T>();
				if (buff != nullptr)
					objs.push_back(buff);

				for (GameObject* child : obj->GetChilds()) {
					T* buff = child->GetComponent<T>();
					if (buff != nullptr)
						objs.push_back(buff);
				}
			}
		}

		std::vector<T*> objs2 = std::move(objs);

		return objs2;
	}

	static __forceinline GameObject* FindObjectByName(std::wstring name)
	{
		Scene* scene = SceneManager::GetActiveScene();

		std::vector<Layer*> mLayers = scene->GetLayers();

		for (Layer* layer : mLayers)
		{
			auto gameObjs = layer->GetGameObjects();
			for (GameObject* obj : gameObjs)
			{
				if (obj->GetName() == name) {
					return obj;
				}
			}
		}

		return nullptr;
	}
}