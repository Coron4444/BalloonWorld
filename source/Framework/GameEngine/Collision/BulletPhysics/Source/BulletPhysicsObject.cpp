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



//****************************************
// �v���p�e�B��`
//****************************************
BulletPhysicsObject::Type BulletPhysicsObject::getType()
{
	return type_;
}



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



Vector3D BulletPhysicsObject::getPosition()
{
	btTransform transform;
	motion_state_->getWorldTransform(transform);
	return Vector3D(transform.getOrigin().getX(), transform.getOrigin().getY(),
				transform.getOrigin().getZ());
}



void BulletPhysicsObject::setPosition(Vector3D value)
{
	btTransform transform;
	motion_state_->getWorldTransform(transform);
	transform.setOrigin(btVector3(value.x, value.y, value.z));
	motion_state_->setWorldTransform(transform);
}



Quaternion BulletPhysicsObject::getQuaternion()
{
	btTransform transform;
	motion_state_->getWorldTransform(transform);
	return Quaternion(transform.getRotation().getX(), transform.getRotation().getY(),
					  transform.getRotation().getZ(), transform.getRotation().getW());
}



void BulletPhysicsObject::setKinematic()
{
	rigid_body_->setCollisionFlags(rigid_body_->getCollisionFlags()
								   | btCollisionObject::CF_KINEMATIC_OBJECT);
	rigid_body_->setActivationState(DISABLE_DEACTIVATION);
}



//****************************************
// �֐���`
//****************************************
void BulletPhysicsObject::InitSphere(float mass, Vector3D* inertia, Vector3D* position,
									 Quaternion* quaternion, float radius)
{
	type_ = BulletPhysicsObject::Type::SPHERE;
	collision_shape_ = new btSphereShape(radius);

	// ���ʏ�����
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::InitOBB(float mass, Vector3D* inertia, Vector3D* position,
								  Quaternion* quaternion, Vector3D* edge_half_length)
{
	type_ = BulletPhysicsObject::Type::OBB;
	collision_shape_ = new btBoxShape(btVector3(edge_half_length->x,
												edge_half_length->y,
												edge_half_length->z));

	// ���ʏ�����
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::InitCapsule(float mass, Vector3D* inertia, Vector3D* position,
									  Quaternion* quaternion, float radius, float height)
{
	type_ = BulletPhysicsObject::Type::CAPSULE;
	collision_shape_ = new btCapsuleShape(radius, height);

	// ���ʏ�����
	InitCommon(mass, inertia, position, quaternion);
}



void BulletPhysicsObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	BulletPhysicsManager::getpInstance()->ReleaseFromTheObjectList(this);
	SafeRelease::Normal(&rigid_body_);
	SafeRelease::Normal(&motion_state_);
	SafeRelease::Normal(&collision_shape_);
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



void BulletPhysicsObject::AddVelocity(Vector3D velocity, Vector3D power_point)
{
	rigid_body_->applyImpulse(btVector3(velocity.x, velocity.y, velocity.z),
							  btVector3(power_point.x, power_point.y, power_point.z));
}



void BulletPhysicsObject::AddAcceleration(Vector3D acceleration, Vector3D power_point)
{
	rigid_body_->applyForce(btVector3(acceleration.x, acceleration.y, acceleration.z),
							btVector3(power_point.x, power_point.y, power_point.z));
}



void BulletPhysicsObject::InitCommon(float mass, Vector3D* inertia,
									 Vector3D* position, Quaternion* quaternion)
{
	// �������[�����g�Z�o
	btVector3 temp_inertia = btVector3(inertia->x, inertia->y, inertia->z);
	collision_shape_->calculateLocalInertia(mass, temp_inertia);

	// �O�����獄�̂𑀍삷��n���h���쐬
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(position->x, position->y, position->z));
	transform.setRotation(btQuaternion(quaternion->x, quaternion->y,
									   quaternion->z, quaternion->w));
	motion_state_ = new btDefaultMotionState(transform);

	// ���̍쐬
	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, motion_state_,
															collision_shape_,
															temp_inertia);
	rigid_body_ = new btRigidBody(rigidbody_info);
	rigid_body_->setAnisotropicFriction(collision_shape_
										->getAnisotropicRollingFrictionDirection(),
										btCollisionObject::
										CF_ANISOTROPIC_ROLLING_FRICTION);
}