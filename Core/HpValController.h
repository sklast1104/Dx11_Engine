#pragma once
#include "Script.h"

namespace Jun::graphics {

	class HpBarMaterial;
}

namespace Jun {

	class HpValController : public Script
	{
	public :

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void DealDamage(float damage);
		void SetPercent(float percent);
		
	private :

		class Jun::graphics::HpBarMaterial* material;
		class Health* health;
	};

}



