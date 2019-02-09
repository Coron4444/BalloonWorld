//================================================================================
//!	@file	 Balloon.cpp
//!	@brief	 風船Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Balloon.h"

#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>



//****************************************
// 定数定義
//****************************************
const Vec3 Balloon::OBB_EDGE_LENGTH_HALF(0.02f, 0.1f, 0.02f);
const float Balloon::SPHERE_RADIUS = 1.0f;



//****************************************
// 関数定義
//****************************************
void Balloon::Init(UpdateBase* update, DrawBase* draw)
{
	// バレットオブジェクト初期化
	InitBulletPhysicsObject();

	// 基底クラスの初期化
	GameObjectBase::Init(update, draw, nullptr);
}



void Balloon::InitBulletPhysicsObject()
{
	// 生成
	float mass = 1.0f;
	Vec3 inertia(0.0f, 0.0f, 0.0f);
	float temp_y = 10.0f;
	Quaternion quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vec3 position(0.0f, temp_y, 0.0f);
	bullet_object_[0] = BulletPhysicsManager::getpInstance()
		->getpObjectSphere(mass, inertia, position,
						   quaternion, SPHERE_RADIUS);
	bullet_object_[0]->getpRigidBody()->setRestitution(1.0f);
	bullet_object_[0]->getpRigidBody()->setRollingFriction(0.1f);
	bullet_object_[0]->getpRigidBody()->setSpinningFriction(0.1f);
	bullet_object_[0]->getpRigidBody()->setDamping(0.7f, 0.3f);

	for (int i = 1; i < MAX_BULLET_OBJECT; i++)
	{
		position = Vec3(0.0f, temp_y - SPHERE_RADIUS - (OBB_EDGE_LENGTH_HALF.y / 2.0f) - OBB_EDGE_LENGTH_HALF.y * 2 * (i - 1), 0.0f);
		if (i == MAX_BULLET_OBJECT - 1)
		{
			mass = 0.0f;
			bullet_object_[i] = BulletPhysicsManager::getpInstance()
				->getpObjectOBB(mass, inertia, position,
								quaternion, OBB_EDGE_LENGTH_HALF);
		}
		else if (i != 0)
		{
			bullet_object_[i] = BulletPhysicsManager::getpInstance()
				->getpObjectOBB(mass, inertia, position,
								quaternion, OBB_EDGE_LENGTH_HALF);
		}
		bullet_object_[i]->getpRigidBody()->setRestitution(1.0f);
		bullet_object_[i]->getpRigidBody()->setRollingFriction(0.1f);
		bullet_object_[i]->getpRigidBody()->setSpinningFriction(0.1f);
		bullet_object_[i]->getpRigidBody()->setDamping(0.7f, 0.3f);
	}

	// 拘束
	float min_max = 0.0f;
	float min_max2 = 0.0f;
	for (int i = 0; i < MAX_BULLET_CONSTRAINT; i++)
	{
		if (i == 0)
		{
			bullet_constraint_[i] = BulletPhysicsManager::getpInstance()
				->setConstraintUniversal(bullet_object_[i], bullet_object_[i + 1],
										 Vec3(bullet_object_[i]->getPosition().x,
											  bullet_object_[i]->getPosition().y - SPHERE_RADIUS,
											  bullet_object_[i]->getPosition().z),
										 -min_max, -min_max, min_max, min_max);
		}
		else
		{
			bullet_constraint_[i] = BulletPhysicsManager::getpInstance()
				->setConstraintUniversal(bullet_object_[i], bullet_object_[i + 1],
										 Vec3(bullet_object_[i]->getPosition().x,
											  bullet_object_[i]->getPosition().y - OBB_EDGE_LENGTH_HALF.y,
											  bullet_object_[i]->getPosition().z),
										 -min_max2, -min_max2, min_max2, min_max2);
		}
	}

	// 行列
	for (int i = 1; i < MAX_BULLET_OBJECT; i++)
	{
		*bullet_transform_[i].getpScale() = OBB_EDGE_LENGTH_HALF * 2.5f;
	}
}