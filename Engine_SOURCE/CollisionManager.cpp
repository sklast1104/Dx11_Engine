#include "CollisionManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Layer.h"
#include "Collider2D.h"

#include <iostream>

namespace Jun
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				//최초 충돌
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
			}
			else
			{
				// 충돌 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f},
			Vector3{0.5f, 0.5f, 0.0f},
			Vector3{0.5f, -0.5f, 0.0f},
			Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector3 leftCenter = leftTr->GetPosition() + Vector3(left->GetCenter().x, left->GetCenter().y, 0.0f);
		Vector3 rightCenter = rightTr->GetPosition() + Vector3(right->GetCenter().x, right->GetCenter().y, 0.0f);

		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);

		Matrix finalLeft = Matrix::CreateScale(leftScale) * leftTr->GetWorldMatrix();
		Matrix finalRight = Matrix::CreateScale(rightScale) * rightTr->GetWorldMatrix();

		//Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		Vector3 vc = leftCenter - rightCenter;
		vc.z = 0.0f;

		if (left->GetType() == eColliderType::Rect && right->GetType() == eColliderType::Rect)
		{
			// 분리축 벡터 4개 구하기
			Vector3 Axis[4] = {};

			Axis[0] = Vector3::Transform(arrLocalPos[1] + left->GetCenter(), finalLeft);
			Axis[1] = Vector3::Transform(arrLocalPos[3] + left->GetCenter(), finalLeft);
			Axis[2] = Vector3::Transform(arrLocalPos[1] + right->GetCenter(), finalRight);
			Axis[3] = Vector3::Transform(arrLocalPos[3] + right->GetCenter(), finalRight);

			Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft) - Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft) - Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight) - Vector3::Transform(arrLocalPos[0], finalRight);
			Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight) - Vector3::Transform(arrLocalPos[0], finalRight);

			for (size_t i = 0; i < 4; i++)
				Axis[i].z = 0.0f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];

				float projDist = 0.0f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}

			return true;
		}
		else if (left->GetType() == eColliderType::Circle && right->GetType() == eColliderType::Circle)
		{
			float leftRadius = left->GetSize().x / 2.0f;
			float rightRadius = right->GetSize().x / 2.0f;
			float totalRadius = leftRadius + rightRadius;

			Vector3 dir = vc;
			float distanceSq = dir.LengthSquared();

			return (distanceSq <= totalRadius * totalRadius);
		}
		else
		{
			Collider2D* circleCollider = (left->GetType() == eColliderType::Circle) ? left : right;
			Collider2D* rectCollider = (left->GetType() == eColliderType::Rect) ? left : right;

			float radius = circleCollider->GetSize().x / 2.0f;
			Vector3 circleCenter = circleCollider->GetOwner()->GetComponent<Transform>()->GetPosition();

			Vector3 rectCorners[4];
			for (size_t i = 0; i < 4; i++)
			{
				rectCorners[i] = Vector3::Transform(arrLocalPos[i], finalRight);
			}

			for (size_t i = 0; i < 4; i++)
			{
				Vector3 dir = rectCorners[i] - circleCenter;
				float distanceSq = dir.LengthSquared();

				if (distanceSq < radius * radius)
				{
					return true;
				}
			}

			return false;
		}
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}
