#include "Animation.h"
#include "MyTime.h"
#include "Animator.h"
#include "Renderer.h"
#include "ConstantBuffer.h"
#include <fstream>

namespace Jun
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{

	}

	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mIndex++;
			mTime = 0.0f;

			if (mSprites.size() <= mIndex)
			{
				mIndex = mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}
	void Animation::Render()
	{
	}
	void Animation::Create(std::wstring name
		, std::shared_ptr<graphics::Texture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		SetKey(name);
		mAtlas = atlas;


		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(200.0f / width, 200.0f / height);
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}

	}

	void Animation::CreateSpineAnim(std::wstring name, std::shared_ptr<graphics::Texture> atlas, const std::wstring& atlasPath, float duration)
	{
		SetKey(name);
		mAtlas = atlas;

		

		std::wifstream file(atlasPath);

		assert(file.is_open());

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		std::wstring line;
		for (int i = 0; i < 2; i++) {
			std::getline(file, line);
		}

		while (std::getline(file, line)) {

			Sprite sprite = {};
			sprite.atlasSize = Vector2(600.0f / width, 600.0f / height);
			sprite.duration = duration;

			// 1036 ~
			std::getline(file, line);

			// bounds ~
			std::getline(file, line);
			std::wstringstream wss(line);

			wchar_t dummy;
			Vector2 bounds;

			wss.ignore(7) >> sprite.leftTop.x >> dummy >> sprite.leftTop.y >> dummy >> sprite.size.x >> dummy >> sprite.size.y;

			std::getline(file, line);

			sprite.leftTop.x = sprite.leftTop.x / width;
			sprite.leftTop.y = sprite.leftTop.y / height;
			sprite.size.x = sprite.size.x / width;
			sprite.size.y = sprite.size.y / height;

			mSprites.push_back(sprite);
		}

		mSprites.pop_back();
	}

	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;
		data.animationType = 1;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}