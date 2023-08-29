#include "UIManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Input.h"
#include "Application.h"
#include "Camera.h"
#include "UI.h"

extern Jun::Application application;

namespace Jun {
	
	void UIManager::Update()
	{
		

	 	Vector2 mousePos = Input::GetMousePos();

		float cursorNdcX = mousePos.x * 2.0f / application.GetWidth() - 1.f;
		float cursorNdcY = -mousePos.y * 2.0f / application.GetHeight() + 1.f;

		cursorNdcX = std::clamp(cursorNdcX, -1.f, 1.f);
		cursorNdcY = std::clamp(cursorNdcY, -1.f, 1.f);

		Matrix viewMat = Camera::GetGpuViewMatrix();
		Matrix projMat = Camera::GetGpuProjectionMatrix();

		Matrix inverseProjView = (viewMat * projMat).Invert();

		Vector3 cursorNdcNear = Vector3(cursorNdcX, cursorNdcY, 0.f);
		Vector3 cursorNdcFar = Vector3(cursorNdcX, cursorNdcY, 1.f);

		Vector3 cursorWorldNear = Vector3::Transform(cursorNdcNear, inverseProjView);
		Vector3 cursorWorldFar = Vector3::Transform(cursorNdcFar, inverseProjView);

		Vector3 dir = cursorWorldFar - cursorWorldNear;
		dir.Normalize();

		Ray ray = Ray(cursorWorldNear, dir);

		Scene* scene = SceneManager::GetActiveScene();

		std::vector<Layer*> mLayers = scene->GetLayers();

		Layer* uiLayer = mLayers[(int)eLayerType::UI];

		auto UIs = uiLayer->GetGameObjects();

		GameObject* minObj = nullptr;

		for (GameObject* ui : UIs) {

			Transform* tr = ui->GetComponent<Transform>();
			
			BoundingOrientedBox box = BoundingOrientedBox(tr->GetPosition(), tr->GetScale(), Quaternion::CreateFromJunwPitchRoll(0.f, 0.f, 0.f));

			float dist = 0.f;
			float maxDist = 0.f;
			
			bool selected = box.Intersects(ray.position, ray.direction, dist);
		
			if (selected && Input::GetKeyDown(eKeyCode::LBUTTON)) {
				if (dist > maxDist) {
					maxDist = dist;
					minObj = ui;
				}
			}
		}

		if (minObj != nullptr) {

			UI* ui = minObj->GetComponent<UI>();
			if (ui) {
				ui->MouseLbtnDown();
			}
		}
	}
	
}