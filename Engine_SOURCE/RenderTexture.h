#pragma once
#include "Texture.h"

namespace Jun::graphics {

	class RenderTexture : public Texture
	{
	public :

		RenderTexture();
		virtual ~RenderTexture();

		virtual HRESULT Load(const std::wstring& path) { return true; };
		bool create(uint32_t xres, uint32_t yres, DXGI_FORMAT new_format, bool is_dynamic);

		bool updateFromIYUV(const uint8_t* new_data, size_t data_size);

		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
		uint32_t xres = 0;
		uint32_t yres = 0;

	private :

	};

}



