#pragma once
#include "State.h"

namespace Jun {

	class MonsterStartState : public State
	{
	private:

		Vector3 dir = { -1.f, 0.f, 0.f };
		Vector3 backOffset = {2.f, 0.f, 0.f};

		Vector3 destPos;
		class Transform* transform;

		float elapsedTime;

		float speed = 1.f;

	public:

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

}



