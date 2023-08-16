#include "Animation.h"
#include "MyTime.h"
#include "Animator.h"
#include "Renderer.h"
#include "ConstantBuffer.h"
#include "Resources.h"
#include <fstream>

namespace Jun
{
	bool IsPng(const std::wstring& wstrline);

	std::wstring ExtractPath(const std::wstring filePath);

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

	void Animation::CreateSpineAnim(std::wstring name,
		const std::wstring& atlasPath, float duration, Vector2 offset, bool isPack)
	{
		SetKey(name);
		//mAtlas = atlas;

		std::wifstream file(atlasPath);

		assert(file.is_open());

		float width = 0.f;
		float height = 0.f;

		std::wstring line;

		std::wstring path = ExtractPath(atlasPath);

		std::shared_ptr<Jun::Texture> curTexture = nullptr;

		while (std::getline(file, line)) {

			if (IsPng(line)) {

				std::wstring newPath = path + line;
				std::wstring newKey = L"Spine_" + line + L"_Tex";

				curTexture = Jun::Resources::Load<Texture>(newKey, newPath);

				// Size
				std::getline(file, line);

				width = (float)curTexture->GetWidth();
				height = (float)curTexture->GetHeight();

				// filter
				std::getline(file, line);
			}

			while (std::getline(file, line) && line != L"") {

				Sprite sprite = {};

				// Bounds
				std::getline(file, line);
				std::wstringstream wss(line);

				wchar_t dummy;
				Vector2 bounds;

				wss.ignore(7) >> sprite.leftTop.x >> dummy >> sprite.leftTop.y >> dummy >> sprite.size.x >> dummy >> sprite.size.y;

				std::getline(file, line);

				float offsetX;
				float offsetY;

				float originSizeX;
				float originSizeY;

				{
					std::wstringstream wss(line);
					wss.ignore(8) >> offsetX >> dummy >> offsetY >> dummy >> originSizeX >> dummy >> originSizeY;
				}

				float whiteSpaceX = originSizeX - sprite.size.x;
				float whiteSpaceY = originSizeY - sprite.size.y;

				float leftOffset = offsetX;
				float bottomOffset = offsetY;
				float rightOffset = whiteSpaceX - leftOffset;
				float topOffset = whiteSpaceY - offsetY;

				sprite.leftTop.x = sprite.leftTop.x / width;
				sprite.leftTop.y = sprite.leftTop.y / height;
				sprite.size.x = sprite.size.x / width;
				sprite.size.y = sprite.size.y / height;

				float realOffsetX = leftOffset;
				float realOffsetY = topOffset / 2;

				mAtlas = curTexture;
				sprite.atlasSize = Vector2(1600.0f / width, 1600.0f / height);
				sprite.duration = duration;

				sprite.offset.x = 0;
				sprite.offset.y = 0;

				sprite.offset.x = realOffsetX / width;
				sprite.offset.y = realOffsetY / height;

				mSprites.push_back(sprite);

				// origin;
				std::getline(file, line);
			}
		}
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