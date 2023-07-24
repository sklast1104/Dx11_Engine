#pragma once
#include "GameObject.h"

namespace Jun {

	class State
	{
	public:
		virtual void Enter() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;

		virtual void FixedUpdate() {};
		virtual void LateUpdate() {};

	public:
		GameObject* owner;

	};

}



