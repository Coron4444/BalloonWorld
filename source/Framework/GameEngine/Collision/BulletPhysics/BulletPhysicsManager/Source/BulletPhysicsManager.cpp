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
}



void BulletPhysicsManager::Uninit()
{
	dynamics_world_->setDebugDrawer(nullptr);
	SafeRelease::Normal(&dynamics_world_);
	SafeRelease::Normal(&solver_);
	SafeRelease::Normal(&broadphase_);
	SafeRelease::Normal(&dispatcher_);
	SafeRelease::Normal(&configuration_);
}



void BulletPhysicsManager::Update()
{
	dynamics_world_->stepSimulation(TIME_STEP, MAX_SUB_STEP);
}