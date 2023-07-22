#pragma once
#include "SceneManager.h"
#include "PlayScene.h"
#include "MainScene.h"
#include "MenuScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\Core.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\Core.lib")
#endif

namespace Jun {

	void InitializeScenes() {
		
		
		SceneManager::CreateScene<MenuScene>(L"MenuScene");
		
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<MainScene>(L"MainScene");
	}
}