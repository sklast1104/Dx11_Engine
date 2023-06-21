#include "CameraScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "MyTime.h"

namespace Jun {



	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}

}