#pragma once
#include "SceneManager.h"
#include "PlayScene.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "QuestScene.h"
#include "BattleScene.h"
#include "QuestMapScene.h"
#include "DebugScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\Core.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\Core.lib")
#endif

namespace Jun {

	void InitializeScenes() {
		
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		
		SceneManager::CreateScene<MenuScene>(L"MenuScene");
		SceneManager::CreateScene<QuestScene>(L"QuestScene");
		//
		
		
		SceneManager::CreateScene<QuestMapScene>(L"QuestMapScene");
		
		SceneManager::CreateScene<MainScene>(L"MainScene");

		//SceneManager::CreateScene <BattleScene>(L"BattleScene");
		
		SceneManager::CreateScene<DebugScene>(L"DebugScene");
	}
}