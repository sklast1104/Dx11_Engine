#pragma once
#include "StateMachine.h"

namespace Jun {

	class PlayerStateMachine : public StateMachine
	{
	public :
		PlayerStateMachine();
		virtual ~PlayerStateMachine();

		virtual void Initialize() override;



	public :
		GameObject* player;
		std::unordered_map<std::wstring, std::shared_ptr<State>> stateMap;
	};


}



