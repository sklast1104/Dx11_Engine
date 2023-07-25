#pragma once
#include "SceneManager.h"
#include "PlayScene.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "QuestScene.h"
#include "BattleScene.h"
#include "QuestMapScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\Core.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\Core.lib")
#endif

namespace Jun {

	void InitializeScenes() {
		
		
		
		SceneManager::CreateScene<MenuScene>(L"MenuScene");
		SceneManager::CreateScene<QuestScene>(L"QuestScene");
		//
		SceneManager::CreateScene <BattleScene>(L"BattleScene");
		SceneManager::CreateScene<MainScene>(L"MainScene");
		SceneManager::CreateScene<QuestMapScene>(L"QuestMapScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
	}
}