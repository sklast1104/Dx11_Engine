#include "Health.h"
#include "GameObject.h"

namespace Jun {

	void Health::Initialize()
	{
		hp = 100.f;
		isAlive = true;
	}
	void Health::Update()
	{
		if (hp <= 0.f) {
			GetOwner()->SetState(GameObject::eState::Dead);
		}
	}
	void Health::LateUpdate()
	{
	}
	void Health::Render()
	{
	}
	void Health::DealDamage(float damage)
	{
		hp -= damage;

		if (hp <= 0.f) isAlive = false;
	}
}