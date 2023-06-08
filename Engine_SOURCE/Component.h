#pragma once
#include "Entity.h"

namespace Jun {

	using namespace Jun::enums;

	class Component : public Entity
	{
	public :
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private :
		const eComponentType mType;
	};

}



