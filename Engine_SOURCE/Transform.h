#pragma once
#include "Component.h"

namespace Jun {

	class Transform : public Component
	{
	public :
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(const Vector3& position) { mPosition = position; }
		void SetRotation(const Vector3& rotation) { mRotation = rotation; }
		void SetScale(const Vector3& scale) { mScale = scale; }

		const Vector3& GetPosition() const { return mPosition; }
		const Vector3& GetRotation() const { return mRotation; }
		const Vector3& GetScale() const { return mScale; }

	private :
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
	};
}



