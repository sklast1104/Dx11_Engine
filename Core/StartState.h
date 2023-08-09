#pragma once
#include "State.h"

namespace Jun {

	class StartState : public State 
	{

	private :
		class Transform* ownerTransform;
		float elapsedTime;

	public :

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	};

}



