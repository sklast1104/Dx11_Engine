#include "SpineAnimation.h"
#include "MyTime.h"
#include "Renderer.h"
#include "Resources.h"
#include <fstream>

namespace Jun {

	SpineAnimation::SpineAnimation()
	{
	}

	SpineAnimation::~SpineAnimation()
	{
	}

	void SpineAnimation::Update()
	{
	}

	void SpineAnimation::LateUpdate()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();

		if (mSpineSprites[mIndex].duration <= mTime) {
			
			mIndex++;
			mTime = 0.f;

			if (mSpineSprites.size() <= mIndex) {
				mIndex = mSpineSprites.size() - 1;
				mbComplete = true;
			}
		}
	}

	void SpineAnimation::Render()
	{
	}

	bool IsPng(const std::wstring& wstrline) {
		std::wstring ext = wstrline.substr(wstrline.size() - 3, 3);
		return ext == L"png";
	}

	std::wstring ExtractPath(const std::wstring filePath) {

		size_t pos = filePath.find_last_of(L"/\\");
		std::wstring path = filePath.substr(0, pos + 1);

		return path;
	}

	void SpineAnimation::CreateSpineAnim(std::wstring name, const std::wstring& atlasPath, float duration, Vector2 offset, bool isPack)
	{
		if (isPack) {
			CreatePackAnim(name, atlasPath, duration, offset);
		}
		else {

			SetKey(name);

			std::wifstream file(atlasPath);

			assert(file.is_open());

			std::wstring line;

			std::shared_ptr<Jun::Texture> curTexture = nullptr;
			float width = 0.f;
			float height = 0.f;

			std::wstring path = ExtractPath(atlasPath);

			// name;
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


				// Name
				while (std::getline(file, line) && line != L"") {

					SpineSprite sprite = {};

					// Bounds
					std::getline(file, line);
					std::wstringstream wss(line);

					wchar_t dummy;
					Vector2 bounds;

					wss.ignore(7) >> sprite.leftTop.x >> dummy >> sprite.leftTop.y >> dummy >> sprite.size.x >> dummy >> sprite.size.y;

					std::getline(file, line);

					float scale = 1.f;

					sprite.leftTop.x = sprite.leftTop.x / width * scale;
					sprite.leftTop.y = sprite.leftTop.y / height * scale;
					sprite.size.x = sprite.size.x / width * scale;
					sprite.size.y = sprite.size.y / height * scale;

					sprite.texture = curTexture;
					sprite.atlasSize = Vector2(600.0f / width, 600.0f / height);
					sprite.duration = duration;
					sprite.offset.x = offset.x / width;
					sprite.offset.y = offset.y / height;

					mSpineSprites.push_back(sprite);
				}
			}
		}
	}

	void SpineAnimation::CreatePackAnim(std::wstring name, const std::wstring& atlasPath, float duration, Vector2 offset)
	{
		SetKey(name);

		std::wifstream file(atlasPath);

		assert(file.is_open());

		std::wstring line;

		std::shared_ptr<Jun::Texture> curTexture = nullptr;
		float width = 0.f;
		float height = 0.f;

		std::wstring path = ExtractPath(atlasPath);

		// name;
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


			// Name
			while (std::getline(file, line) && line != L"") {

				SpineSprite sprite = {};

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

				float realOffsetX = (leftOffset-rightOffset) / 2;
				float realOffsetY = (topOffset-bottomOffset) / 2;

				sprite.leftTop.x = sprite.leftTop.x / width;
				sprite.leftTop.y = sprite.leftTop.y / height;
				sprite.size.x = sprite.size.x / width;
				sprite.size.y = sprite.size.y / height;

				sprite.texture = curTexture;
				sprite.atlasSize = Vector2(800.0f / width, 800.0f / height);
				sprite.duration = duration;
				sprite.offset.x = (realOffsetX + offset.x) / width;
				sprite.offset.y = (realOffsetY + offset.y) / height;

				mSpineSprites.push_back(sprite);

				// origin;
				std::getline(file, line);
			}
		}
	}

	void SpineAnimation::Binds()
	{
		mSpineSprites[mIndex].texture->BindShaderResource(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSpineSprites[mIndex].leftTop;
		data.spriteSize = mSpineSprites[mIndex].size;
		data.spriteOffset = mSpineSprites[mIndex].offset;
		data.atlasSize = mSpineSprites[mIndex].atlasSize;
		data.animationType = 1;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void SpineAnimation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}

}