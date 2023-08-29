#pragma once
#include "Component.h"
#include "Collider2D.h"

namespace Jun {

	class Script : public Component
	{
	public :

		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {};
		virtual void OnCollisionStay(Collider2D* other) {};
		virtual void OnCollisionExit(Collider2D* other) {};

		virtual void MouseOn() {};
		virtual void MouseLbtnUp() {};
		virtual void MouseLbtnDown() {};
		virtual void MouseLbtnClicked() {};

	private :



	};


}


