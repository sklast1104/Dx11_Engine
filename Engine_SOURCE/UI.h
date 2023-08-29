#pragma once
#include "Component.h"

namespace Jun {

	class UI : public Component
	{
	private :



	public :

		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void MouseOn();
		void MouseLbtnUp();
		void MouseLbtnDown();
		void MouseLbtnClicked();

	};
}

