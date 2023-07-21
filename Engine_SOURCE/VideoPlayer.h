#pragma once
#include "Component.h"
#include "RenderTexture.h"

namespace Jun {

	class VideoPlayer : public Component
	{
	public :

		VideoPlayer();
		~VideoPlayer();

		static bool CreateAPI();
		static void DestoryAPI();

		virtual void Initialize() override;
		virtual void Update() override;

		struct InternalData;
		std::shared_ptr<InternalData> mData = nullptr;

		bool Create(const std::string& path);

		void Pause();
		void Resume();
		bool hasFinished();

		static std::shared_ptr<Jun::graphics::RenderTexture> mRenderTexture;
	};

}



