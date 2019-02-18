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
#include <Tool/MeterToFrame.h>



//****************************************
// 定数定義
//****************************************
const Vec3 Balloon::OBB_EDGE_LENGTH_HALF(0.02f, 0.1f, 0.02f);
const float Balloon::SPHERE_RADIUS = 1.0f;
const float Balloon::RISING_SPEED
= MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(1000000.0f);



//****************************************
// プロパティ定義
//****************************************
int Balloon::getAllObjectNum()
{
	return all_object_.size();
}



int Balloon::getObjectConstraintNum()
{
	return object_constraint_.size();
}




BulletPhysicsObject* Balloon::getpObject(unsigned index)
{
	return all_object_[index];
}



BulletPhysicsConstraint* Balloon::getpObjectConstraint(unsigned index)
{
	return object_constraint_[index];
}



Vec3 Balloon::getPosition()
{
	return all_object_[0]->getPosition();
}



void Balloon::setPosition(Vec3 value)
{
	all_object_[0]->setPosition(value);
}



//****************************************
// 関数定義
//****************************************
void Balloon::Init(DrawBase* draw, unsigned balloon_line_num)
{
	// バレットオブジェクト初期化
	InitBulletPhysicsObject(balloon_line_num);

	// 基底クラスの初期化
	GameObjectBase::Init(draw, nullptr);
}



void Balloon::Update()
{
	// 上昇
	getpObject(getAllObjectNum() - 1)->getpRigidBody()->activate();
	getpObject(getAllObjectNum() - 1)->AddAcceleration(Vec3(0.0f, RISING_SPEED, 0.0f),
													   Vec3(0.0f, 1.0f, 0.0f));
}



void Balloon::ReleaseConstraint(unsigned index)
{
	object_constraint_[index]->Release();
	object_constraint_[index] = nullptr;
}



void Balloon::ReleaseBaseConstraint()
{
	ReleaseConstraint(0);
}



void Balloon::AddVelocity(Vec3 velocity)
{
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->activate();
	all_object_[getAllObjectNum() - 1]->AddVelocity(velocity);
}



void Balloon::AddAcceleration(Vec3 acceleration)
{
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->activate();
	all_object_[getAllObjectNum() - 1]->AddAcceleration(acceleration);
}



void Balloon::InitBulletPhysicsObject(unsigned balloon_line_num)
{
	// バレットオブジェクト数確定
	all_object_.resize(balloon_line_num);
	object_constraint_.resize(balloon_line_num - 1);

	// 紐の生成
	float mass = 1.0f;
	Vec3 inertia(0.0f, 0.0f, 0.0f);
	Quaternion quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vec3 position(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < getAllObjectNum() - 1; i++)
	{
		position = Vec3(0.0f, OBB_EDGE_LENGTH_HALF.y * 2 * i, 0.0f);
		if (i == 0)
		{
			mass = 0.0f;
			all_object_[i] = BulletPhysicsManager::getpInstance()
				->getpObjectOBB(mass, inertia, position,
								quaternion, OBB_EDGE_LENGTH_HALF);
			all_object_[i]->setKinematic();
		}
		else if (i != 0)
		{
			mass = 1.0f;
			all_object_[i] = BulletPhysicsManager::getpInstance()
				->getpObjectOBB(mass, inertia, position,
								quaternion, OBB_EDGE_LENGTH_HALF);
		}
		all_object_[i]->getpRigidBody()->setRestitution(1.0f);
		all_object_[i]->getpRigidBody()->setRollingFriction(0.1f);
		all_object_[i]->getpRigidBody()->setSpinningFriction(0.1f);
		all_object_[i]->getpRigidBody()->setDamping(0.7f, 0.3f);
	}

	// 風船の生成
	position = Vec3(0.0f, OBB_EDGE_LENGTH_HALF.y * 2 * (getAllObjectNum() - 2) + OBB_EDGE_LENGTH_HALF.y + SPHERE_RADIUS, 0.0f);
	all_object_[getAllObjectNum() - 1] = BulletPhysicsManager::getpInstance()
		->getpObjectSphere(mass, inertia, position, quaternion, SPHERE_RADIUS);
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->setRestitution(1.0f);
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->setRollingFriction(0.1f);
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->setSpinningFriction(0.1f);
	all_object_[getAllObjectNum() - 1]->getpRigidBody()->setDamping(0.7f, 0.3f);

	// 拘束
	float min_max = 0.0f;
	float min_max2 = 0.0f;
	for (int i = 0; i < getObjectConstraintNum(); i++)
	{
		Vec3 temp_position = all_object_[i]->getPosition();
		if (i == (getObjectConstraintNum() - 1))
		{
			object_constraint_[i] = BulletPhysicsManager::getpInstance()
				->setConstraintHinge(all_object_[i], all_object_[i + 1],
									 Vec3(0.0f, OBB_EDGE_LENGTH_HALF.y, 0.0f),
									 Vec3(0.0f, -SPHERE_RADIUS, 0.0f),
									 -min_max, min_max);
		}
		else
		{
			object_constraint_[i] = BulletPhysicsManager::getpInstance()
				->setConstraintHinge(all_object_[i], all_object_[i + 1],
									 Vec3(0.0f, OBB_EDGE_LENGTH_HALF.y, 0.0f),
									 Vec3(0.0f, -OBB_EDGE_LENGTH_HALF.y, 0.0f),
									 -min_max2, min_max2);
		}
	}
}