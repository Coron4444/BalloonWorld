//================================================================================
//!	@file	 BulletPhysicsManager.cpp
//!	@brief	 �o���b�g�t�B�W�b�N�X�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BulletPhysicsManager.h"
#include "../../BulletPhysicsDebug.h"


#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const btVector3 BulletPhysicsManager::DEFULT_GRAVITY(0.0f, -9.8f, 0.0f);
const btScalar BulletPhysicsManager::TIME_STEP = 1.0f / 60.0f;
const int BulletPhysicsManager::MAX_SUB_STEP = 10;



//****************************************
// static�ϐ���`
//****************************************
BulletPhysicsManager* BulletPhysicsManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
BulletPhysicsManager* BulletPhysicsManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new BulletPhysicsManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void BulletPhysicsManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
void BulletPhysicsManager::setDebug(bool value)
{
	if (value)
	{
		debug_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}
	else
	{
		debug_->setDebugMode(btIDebugDraw::DBG_NoDebug);
	}
}



btDefaultMotionState* BulletPhysicsManager::getpMotionState()
{
	return motion_state_[0];
}



//****************************************
// �֐���`
//****************************************
BulletPhysicsManager::BulletPhysicsManager()
{
}



void BulletPhysicsManager::Init()
{
	// �Փˌv�Z�̐ݒ�(����̓f�t�H���g���g�p)
	configuration_ = new btDefaultCollisionConfiguration();
	dispatcher_ = new btCollisionDispatcher(configuration_);

	// �u���[�h�t�F�[�Y�@(�Փ˂���\���̂���I�u�W�F�N�g�̌��o)�̐ݒ�(�����Octree)
	broadphase_ = new btDbvtBroadphase();

	// �S���\���o�ݒ�(�I�u�W�F�N�g�̏d�Ȃ�����Ȃǂ̐ݒ�)
	solver_ = new btSequentialImpulseConstraintSolver();

	// bullet���[���h�ݒ�
	dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, solver_, configuration_);
	dynamics_world_->setGravity(DEFULT_GRAVITY);

	// �f�o�b�O������
	debug_ = new BulletPhysicsDebug();
	debug_->Init();
	dynamics_world_->setDebugDrawer(debug_);

	// ��
	btCollisionShape* temp_shape = new btSphereShape(1.0f);
	btScalar mass = 20.0f;
	btVector3 inertia(0.0f, 0.0f, 0.0f);
	temp_shape->calculateLocalInertia(mass, inertia);
	shape_.push_back(temp_shape);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0.0f, 20.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 0, 0, 1));
	btDefaultMotionState* temp_motion_state = new btDefaultMotionState(transform);
	motion_state_.push_back(temp_motion_state);

	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, temp_motion_state,
															temp_shape, inertia);
	btRigidBody* temp_rigid_body = new btRigidBody(rigidbody_info);
	dynamics_world_->addRigidBody(temp_rigid_body);
	rigid_body_.push_back(temp_rigid_body);

	// ��2
	temp_shape = new btSphereShape(1.0f);
	mass = 1.0f;
	inertia = btVector3(0.0f, 0.0f, 0.0f);
	temp_shape->calculateLocalInertia(mass, inertia);
	shape_.push_back(temp_shape);

	transform.setIdentity();
	transform.setOrigin(btVector3(1.0f, 1.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 0, 0, 1));
	temp_motion_state = new btDefaultMotionState(transform);
	motion_state_.push_back(temp_motion_state);

	rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(mass, temp_motion_state,
															  temp_shape, inertia);
	temp_rigid_body = new btRigidBody(rigidbody_info);
	dynamics_world_->addRigidBody(temp_rigid_body);
	rigid_body_.push_back(temp_rigid_body);

	// �`��̑g�ݍ��킹
	comp_ = new btCompoundShape();
	mass = 1.0f;
	inertia = btVector3(0.0f, 0.0f, 0.0f);
	comp_->calculateLocalInertia(mass, inertia);

	comp_shape_[0] = new btCapsuleShape(1.0f, 3.0f);
	transform.setIdentity();
	transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 1, 0, 1));
	comp_->addChildShape(transform, comp_shape_[0]);

	comp_shape_[1] = new btBoxShape(btVector3(1.0f, 1.0f, 3.0f));
	transform.setIdentity();
	transform.setOrigin(btVector3(2.0f, 2.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 1, 0, 1));
	comp_->addChildShape(transform, comp_shape_[1]);

	transform.setIdentity();
	transform.setOrigin(btVector3(2.0f, 10.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 0, 0, 1));
	comp_motion_state_ = new btDefaultMotionState(transform);

	rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(mass, comp_motion_state_,
															  comp_, inertia);
	comp_rigid_body_ = new btRigidBody(rigidbody_info);
	dynamics_world_->addRigidBody(comp_rigid_body_);

	// �n��
	ground_ = new btBoxShape(btVector3(50.0f, 50.0f, 50.0f));
	mass = 0.0f;
	inertia = btVector3(0.0f, 0.0f, 0.0f);
	ground_->calculateLocalInertia(mass, inertia);

	transform.setIdentity();
	transform.setOrigin(btVector3(0.0f, -50.0f, 0.0f));		// ���s�ړ�
	ground_motion_state_ = new btDefaultMotionState(transform);

	rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(mass, ground_motion_state_,
															  ground_, inertia);
	ground_rigid_body_ = new btRigidBody(rigidbody_info);

	dynamics_world_->addRigidBody(ground_rigid_body_);
}



void BulletPhysicsManager::Uninit()
{
	dynamics_world_->setDebugDrawer(nullptr);
	SafeRelease::Normal(&dynamics_world_);

	for (unsigned i = 0; i < rigid_body_.size(); i++)
	{
		SafeRelease::Normal(&rigid_body_[i]);
		SafeRelease::Normal(&motion_state_[i]);
		SafeRelease::Normal(&shape_[i]);
	}

	SafeRelease::Normal(&comp_rigid_body_);
	SafeRelease::Normal(&comp_motion_state_);
	SafeRelease::Normal(&comp_);
	SafeRelease::Normal(&comp_shape_[0]);
	SafeRelease::Normal(&comp_shape_[1]);

	SafeRelease::Normal(&ground_rigid_body_);
	SafeRelease::Normal(&ground_motion_state_);
	SafeRelease::Normal(&ground_);

	SafeRelease::Normal(&debug_);
	SafeRelease::Normal(&solver_);
	SafeRelease::Normal(&broadphase_);
	SafeRelease::Normal(&dispatcher_);
	SafeRelease::Normal(&configuration_);
}



void BulletPhysicsManager::Update()
{
	dynamics_world_->stepSimulation(TIME_STEP, MAX_SUB_STEP);
}



void BulletPhysicsManager::DrawDebug(Camera* camera)
{
	debug_->DrawSettingBefore(camera);
	dynamics_world_->debugDrawWorld();
	debug_->DrawSettingAfter();
}