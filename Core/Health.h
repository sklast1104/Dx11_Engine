#pragma once
#include "Script.h"

namespace Jun {

	class Health : public Script
	{
	private :
		bool isAlive;

	public :
		float hp;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool IsAlive() { return isAlive; }

		void DealDamage(float damage);
	};
}



