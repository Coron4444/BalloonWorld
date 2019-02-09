//================================================================================
//!	@file	 BulletPhysicsConstraint.cpp
//!	@brief	 �o���b�g�t�B�W�b�N�X�S��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/09
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BulletPhysicsConstraint.h"
#include "../BulletPhysicsManager/BulletPhysicsManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
void BulletPhysicsConstraint::InitPointToPoint(btRigidBody* rigid_body0,
											   btRigidBody* rigid_body1,
											   Vec3* point0, Vec3* point1)
{
	constraint_ = new btPoint2PointConstraint(*rigid_body0, *rigid_body1,
											  btVector3(point0->x, point0->y, point0->z),
											  btVector3(point1->x, point1->y, point1->z));
}



void BulletPhysicsConstraint::InitUniversal(btRigidBody* rigid_body0,
											btRigidBody* rigid_body1, Vec3* anchor,
											float angle_min0, float angle_min1,
											float angle_max0, float angle_max1,
											Vec3* axis0, Vec3* axis1)
{
	constraint_ = new btUniversalConstraint(*rigid_body0, *rigid_body1,
											btVector3(anchor->x, anchor->y, anchor->z),
											btVector3(axis0->x, axis0->y, axis0->z),
											btVector3(axis1->x, axis1->y, axis1->z));
	
	((btUniversalConstraint*)constraint_)->setLowerLimit(angle_min0, angle_max0);
	((btUniversalConstraint*)constraint_)->setLowerLimit(angle_min1, angle_max1);
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