#include "MonsterStandByState.h"
#include "MyTime.h"
#include "MonsterStateMachine.h"
#include "SkeletonMecanim.h"

#include <random>

namespace Jun {

    void MonsterStandByState::Enter()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 0.5f);
        float randomValue = dist(gen);

        delay = 2.f;
        delay += randomValue;

        elapsedTime = 0.f;

        owner->GetComponent<SkeletonMecanim>()->PlayAnimation(L"Idle", true);
    }

    void MonsterStandByState::Update()
    {
        elapsedTime += Time::DeltaTime();

        if (elapsedTime > delay) {

            MonsterStateMachine* machine = owner->GetComponent<MonsterStateMachine>();
            machine->SwitchState(machine->stateMap[L"IdleState"].get());

        }
    }

    void MonsterStandByState::Exit()
    {
    }

}