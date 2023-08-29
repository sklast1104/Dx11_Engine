#pragma once
#include "StateMachine.h"

namespace Jun {

	class MonsterStateMachine : public StateMachine
	{
	public :

		MonsterStateMachine();
		virtual ~MonsterStateMachine();

		virtual void Initialize() override;
		virtual void Start() override;


	public :
		GameObject* monster;
	};


}


