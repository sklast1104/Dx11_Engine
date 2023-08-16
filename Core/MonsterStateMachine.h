#pragma once
#include "StateMachine.h"

namespace Jun {

	class MonsterStateMachine : public StateMachine
	{
	public :

		MonsterStateMachine();
		virtual ~MonsterStateMachine();

		virtual void Initialize() override;


	public :
		GameObject* monster;
	};


}


