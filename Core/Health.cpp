#include "Health.h"
#include "GameObject.h"

namespace Jun {

	void Health::Initialize()
	{
		hp = 100.f;
		maxHp = 100.f;
		isAlive = true;
	}
	void Health::Update()
	{

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
	float Health::GetPercent()
	{
		float percent = hp / maxHp;

		return percent;
	}
}