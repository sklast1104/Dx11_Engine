#pragma once
#include "Animator.h"

namespace Jun {

	class SkeletonMecanim : public Animator
	{
	public:
		SkeletonMecanim();
		virtual ~SkeletonMecanim();

		virtual void Create(const std::wstring& name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f) {};

		virtual void Create(const std::wstring& name,
			const std::wstring& atlasPath,
			float duration = 0.1f,
			Vector2 offset = Vector2::Zero);
	};

}



