#include "SkeletonMecanim.h"
#include "SpineAnimation.h"

namespace Jun {



    SkeletonMecanim::SkeletonMecanim()
    {
    }

    SkeletonMecanim::~SkeletonMecanim()
    {
    }

    void SkeletonMecanim::Create(const std::wstring& name, const std::wstring& atlasPath, float duration, Vector2 offset)
    {
        Animation* animation = FindAnimation(name);
        if (nullptr != animation)
            return;

        animation = new SpineAnimation();
        animation->SetKey(name);

        animation->CreateSpineAnim(name, atlasPath, duration, offset);

        mAnimations.insert(std::make_pair(name, animation));

        Events* events = FindEvents(name);
        if (events != nullptr)
            return;

        events = new Events();
        mEvents.insert(std::make_pair(name, events));
    }

}