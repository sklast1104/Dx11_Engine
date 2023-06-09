#pragma once
#include "Component.h"
#include "Transform.h"


namespace Jun
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		void SetRadius(float radius) { mRadius = radius; }
		
		UINT GetColliderID() { return mColliderID; }
		eColliderType GetType() { return mType; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
		float mRadius;

	};
}
