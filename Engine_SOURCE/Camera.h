#pragma once
#include "Component.h"
#include "Graphics.h"

namespace Jun {

	class Camera : public Component
	{
	public :
		Camera();
		~Camera();

	private :
		static Matrix mView;
		static Matrix mProjection;
	};

}



