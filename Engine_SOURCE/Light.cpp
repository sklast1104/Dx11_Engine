#include "Light.h"
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

namespace Jun
{
	Light::Light()
		: Component(eComponentType::Light)
	{
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::LateUpdate()
	{
		renderer::lights.push_back(this);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(tr->Foward().x, tr->Foward().y, tr->Foward().z, 1.0f);
	}

	void Light::Render()
	{

	}
}
