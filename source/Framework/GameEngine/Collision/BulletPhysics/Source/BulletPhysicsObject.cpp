//================================================================================
//!	@file	 BulletPhysicsObject.cpp
//!	@brief	 バレットフィジックスオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BulletPhysicsObject.h"
#include "../BulletPhysicsManager/BulletPhysicsManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
btCollisionShape* BulletPhysicsObject::getpCollisionShape()
{
	return collision_shape_;
}



btDefaultMotionState* BulletPhysicsObject::getpMotionState()
{
	return motion_state_;
}



btRigidBody* BulletPhysicsObject::getpRigidBody()
{
	return rigid_body_;
}



//****************************************
// 関数定義
//****************************************
void BulletPhysicsObject::InitSphere(float mass, btVector3 inertia,
									 btVector3 position, btQuaternion quaternion,
									 float radius)
{

	collision_shape_ = new btSphereShape(radius);

	// 共通初期化
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::InitOBB(float mass, btVector3 inertia,
								  btVector3 position, btQuaternion quaternion,
								  btVector3 edge_half_length)
{

	collision_shape_ = new btBoxShape(edge_half_length);

	// 共通初期化
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	SafeRelease::Normal(&rigid_body_);
	SafeRelease::Normal(&motion_state_);
	SafeRelease::Normal(&collision_shape_);

	BulletPhysicsManager::getpInstance()->ReleaseFromTheList(this);
	delete this;
}



void BulletPhysicsObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void BulletPhysicsObject::AddReferenceCounter()
{
	reference_counter_++;
}



void BulletPhysicsObject::InitCommon(float mass, btVector3 inertia,
									 btVector3 position, btQuaternion quaternion)
{
	// 慣性モーメント算出
	collision_shape_->calculateLocalInertia(mass, inertia);

	// 外部から剛体を操作するハンドル作成
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);
	transform.setRotation(quaternion);
	motion_state_ = new btDefaultMotionState(transform);

	// 剛体作成
	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, motion_state_,
															collision_shape_, inertia);
	rigid_body_ = new btRigidBody(rigidbody_info);
	rigid_body_->setAnisotropicFriction(collision_shape_->getAnisotropicRollingFrictionDirection(),
										btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
}