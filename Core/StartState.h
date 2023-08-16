#pragma once
#include "State.h"

namespace Jun::PlayerState {

	class StartState : public State 
	{

	private :
		class Transform* ownerTransform;
		Vector3 destPos;
		float elapsedTime;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};

}



