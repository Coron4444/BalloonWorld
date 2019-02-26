//================================================================================
//!	@file	 BulletPhysicsConstraint.cpp
//!	@brief	 バレットフィジックス拘束Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/09
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BulletPhysicsConstraint.h"
#include "../BulletPhysicsManager/BulletPhysicsManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
btTypedConstraint* BulletPhysicsConstraint::getpConstraint()
{
	return constraint_;
}



BulletPhysicsConstraint::Type BulletPhysicsConstraint::getType()
{
	return type_;
}



//****************************************
// 関数定義
//****************************************
void BulletPhysicsConstraint::InitPointToPoint(btRigidBody* rigid_body0,
											   btRigidBody* rigid_body1,
											   Vector3D* point0, Vector3D* point1)
{
	constraint_ = new btPoint2PointConstraint(*rigid_body0, *rigid_body1,
											  btVector3(point0->x, point0->y, point0->z),
											  btVector3(point1->x, point1->y, point1->z));
}



void BulletPhysicsConstraint::InitHinge(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
										Vector3D* point0, Vector3D* point1,
										float angle_min, float angle_max, Vector3D* axis)
{
	constraint_ = new btHingeConstraint(*rigid_body0, *rigid_body1,
										btVector3(point0->x, point0->y, point0->z),
										btVector3(point1->x, point1->y, point1->z),
										btVector3(axis->x, axis->y, axis->z),
										btVector3(axis->x, axis->y, axis->z));
	
	((btHingeConstraint*)constraint_)->setLimit(angle_min, angle_max);
}



void BulletPhysicsConstraint::InitUniversal(btRigidBody* rigid_body0,
											btRigidBody* rigid_body1, Vector3D* anchor,
											float angle_min0, float angle_min1,
											float angle_max0, float angle_max1,
											Vector3D* axis0, Vector3D* axis1)
{
	constraint_ = new btUniversalConstraint(*rigid_body0, *rigid_body1,
											btVector3(anchor->x, anchor->y, anchor->z),
											btVector3(axis0->x, axis0->y, axis0->z),
											btVector3(axis1->x, axis1->y, axis1->z));

	((btUniversalConstraint*)constraint_)->setLowerLimit(angle_min0, angle_min1);
	((btUniversalConstraint*)constraint_)->setUpperLimit(angle_max0, angle_max1);
}



void BulletPhysicsConstraint::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	BulletPhysicsManager::getpInstance()->ReleaseFromTheConstraintList(this);
	SafeRelease::Normal(&constraint_);
	delete this;
}



void BulletPhysicsConstraint::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void BulletPhysicsConstraint::AddReferenceCounter()
{
	reference_counter_++;
}