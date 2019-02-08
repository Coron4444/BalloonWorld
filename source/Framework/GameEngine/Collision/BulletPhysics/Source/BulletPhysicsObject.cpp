//================================================================================
//!	@file	 BulletPhysicsObject.cpp
//!	@brief	 �o���b�g�t�B�W�b�N�X�I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BulletPhysicsObject.h"
#include "../BulletPhysicsManager/BulletPhysicsManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
void BulletPhysicsObject::InitSphere(float mass, btVector3 inertia,
									 btVector3 position, btQuaternion quaternion,
									 float radius)
{

	collision_shape_ = new btSphereShape(radius);

	// ���ʏ�����
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::InitOBB(float mass, btVector3 inertia,
								  btVector3 position, btQuaternion quaternion,
								  btVector3 edge_half_length)
{

	collision_shape_ = new btBoxShape(edge_half_length);

	// ���ʏ�����
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
	// �������[�����g�Z�o
	collision_shape_->calculateLocalInertia(mass, inertia);

	// �O�����獄�̂𑀍삷��n���h���쐬
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(position);
	transform.setRotation(quaternion);
	motion_state_ = new btDefaultMotionState(transform);

	// ���̍쐬
	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, motion_state_,
															collision_shape_, inertia);
	rigid_body_ = new btRigidBody(rigidbody_info);
	rigid_body_->setAnisotropicFriction(collision_shape_->getAnisotropicRollingFrictionDirection(),
										btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
}