#pragma once
#include "Animation.h"

namespace Jun {

	class SpineAnimation : public Animation
	{
	public :

		struct SpineSprite {
			std::shared_ptr<Texture> texture;
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 atlasSize;
			float duration;

			SpineSprite()
				: texture(nullptr)
				, leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		SpineAnimation();
		~SpineAnimation();

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void Create(std::wstring name
			, std::shared_ptr<graphics::Texture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.0f) {};

		virtual void CreateSpineAnim(std::wstring name,
			const std::wstring& atlasPath,
			float duration = 0.0f,
			Vector2 offset = Vector2::Zero, 
			bool isPack = false) override;

		void CreatePackAnim(std::wstring name,
			const std::wstring& atlasPath,
			float duration = 0.0f,
			Vector2 offset = Vector2::Zero);

		virtual void Binds();
		virtual void Reset();

	private :

		std::vector<std::shared_ptr<graphics::Texture>> atlases;
		std::vector<SpineSprite> mSpineSprites;

	};

}



