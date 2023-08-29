#include "MainUIHandler.h"
#include "SceneManager.h"
#include "Object.h"
#include "GameObject.h"
#include "SimpleFadeHandler.h"

namespace Jun {

	using namespace Jun::object;

	void MainUIHandler::Initialize()
	{
	}
	void MainUIHandler::Start()
	{
	}
	void MainUIHandler::Update()
	{
	}
	void MainUIHandler::LateUpdate()
	{
	}
	void MainUIHandler::Render()
	{
	}
	void MainUIHandler::MouseLbtnDown(){

		SimpleFadeHandler* handler = FindObjectOfType<SimpleFadeHandler>();

		handler->StartFade();

		//SceneManager::LoadScene(L"MenuScene");
	}
}