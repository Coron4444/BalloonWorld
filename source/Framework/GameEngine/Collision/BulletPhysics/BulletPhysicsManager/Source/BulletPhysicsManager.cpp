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
#include <GameEngine/Input/InputManager/InputManager.h>


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
	//solver_ = new btSequentialImpulseConstraintSolver();
	solver_ = new btMultiBodyConstraintSolver();

	// bullet���[���h�ݒ�
	//dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, solver_, configuration_);
	dynamics_world_ = new btMultiBodyDynamicsWorld(dispatcher_, broadphase_,
		(btMultiBodyConstraintSolver*)solver_, configuration_);
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
	transform.setOrigin(btVector3(0.0f, 10.0f, 0.0f));		// ���s�ړ�
	transform.setRotation(btQuaternion(0, 0, 0, 1));
	btDefaultMotionState* temp_motion_state = new btDefaultMotionState(transform);
	motion_state_.push_back(temp_motion_state);

	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, temp_motion_state,
															temp_shape, inertia);
	btRigidBody* temp_rigid_body = new btRigidBody(rigidbody_info);
	temp_rigid_body->setRestitution(1.0f);
	temp_rigid_body->setRollingFriction(0.1f);
	temp_rigid_body->setSpinningFriction(0.1f);
	temp_rigid_body->setAnisotropicFriction(temp_shape->getAnisotropicRollingFrictionDirection(),
											btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
	dynamics_world_->addRigidBody(temp_rigid_body);
	rigid_body_.push_back(temp_rigid_body);

	// ��2
	temp_shape = new btSphereShape(1.0f);
	mass = 1.0f;
	inertia = btVector3(-2.0f, 0.0f, 0.0f);
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
	temp_rigid_body->setRestitution(1.0f);
	temp_rigid_body->setRollingFriction(0.1f);
	temp_rigid_body->setSpinningFriction(0.1f);
	temp_rigid_body->setAnisotropicFriction(temp_shape->getAnisotropicRollingFrictionDirection(),
											btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
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
	comp_rigid_body_->setRestitution(1.0f);
	comp_rigid_body_->setRollingFriction(0.1f);
	comp_rigid_body_->setSpinningFriction(0.1f);
	comp_rigid_body_->setDamping(0.7f, 1.0f);
	comp_rigid_body_->setAnisotropicFriction(comp_->getAnisotropicRollingFrictionDirection(),
											 btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
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
	ground_rigid_body_->setRestitution(0.0f);
	//ground_rigid_body_->setFriction(0.0f);
	dynamics_world_->addRigidBody(ground_rigid_body_);

	// �S��
	btVector3 box_half(0.05f, 0.37f, 0.1f);
	for (int i = 0; i < 4; i++)
	{
		if (i != 0)
		{
			temp_shape = new btBoxShape(box_half);
		}
		else
		{
			temp_shape = new btSphereShape(1.0f);
		}
		mass = 1.0f;
		inertia = btVector3(0.0f, 0.0f, 0.0f);
		temp_shape->calculateLocalInertia(mass, inertia);
		constraint_shape_.push_back(temp_shape);

		transform.setIdentity();
		transform.setOrigin(btVector3(0.0f, 6.0f - box_half.getY() * 2 * i, 0.0f));		// ���s�ړ�
		transform.setRotation(btQuaternion(0, 0, 0, 1));
		temp_motion_state = new btDefaultMotionState(transform);
		constraint_motion_state_.push_back(temp_motion_state);

		rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(mass, temp_motion_state,
																  temp_shape, inertia);
		temp_rigid_body = new btRigidBody(rigidbody_info);
		temp_rigid_body->setRestitution(1.0f);
		temp_rigid_body->setRollingFriction(0.1f);
		temp_rigid_body->setSpinningFriction(0.1f);
		//temp_rigid_body->setDamping(0.7f, 1.0f);
		temp_rigid_body->setAnisotropicFriction(temp_shape->getAnisotropicRollingFrictionDirection(),
												btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
		dynamics_world_->addRigidBody(temp_rigid_body);
		constraint_rigid_body_.push_back(temp_rigid_body);
	}

	btPoint2PointConstraint* temp_const = new btPoint2PointConstraint(*constraint_rigid_body_[0],
																	  *constraint_rigid_body_[1],
																	  btVector3(0.0f, -1.0f, 0.0f),
																	  btVector3(0.0f, box_half.getY(), 0.0f));
	dynamics_world_->addConstraint(temp_const);
	constraint_.push_back(temp_const);

	temp_const = new btPoint2PointConstraint(*constraint_rigid_body_[1],
											 *constraint_rigid_body_[2],
											 btVector3(0.0f, -box_half.getY(), 0.0f),
											 btVector3(0.0f, box_half.getY(), 0.0f));
	dynamics_world_->addConstraint(temp_const);
	constraint_.push_back(temp_const);

	temp_const = new btPoint2PointConstraint(*constraint_rigid_body_[2],
											 *constraint_rigid_body_[3],
											 btVector3(0.0f, -box_half.getY(), 0.0f),
											 btVector3(0.0f, box_half.getY(), 0.0f));
	dynamics_world_->addConstraint(temp_const);
	constraint_.push_back(temp_const);

	temp_const = new btPoint2PointConstraint(*constraint_rigid_body_[3],
											 *ground_rigid_body_,
											 btVector3(0.0f, -box_half.getY(), 0.0f),
											 btVector3(0.0f, 50.0f, 0.0f));
	dynamics_world_->addConstraint(temp_const);
	constraint_.push_back(temp_const);

	/*
	// ���}���`�{�f�B(�x�[�X+�����I�u�W�F�N�g)
	// �x�[�X�̊������[�����g�v�Z
	btVector3 base_inertia(0.0f, 0.0f, 0.0f);
	float base_mass = 1.0f;
	btVector3 base_half_extents(0.05f, 0.37f, 0.1f);
	btBoxShape* temp_box = new btBoxShape(base_half_extents);
	temp_box->calculateLocalInertia(base_mass, base_inertia);
	delete temp_box;

	// �}���`�{�f�B�쐬
	int link_num = 5;
	bool fixed_base = true;		// �x�[�X�I�u�W�F�N�g���Œ肷�邩�t���O
	bool can_sleep = false;		// �X���[�v��Ԃɂ��Ă������t���O
	multi_body_ = new btMultiBody(link_num, base_mass, base_inertia,
								  fixed_base, can_sleep);

	// �x�[�X��Transform�o�^
	btVector3 base_position(0.0f, 5.0f, 0.0f);
	btQuaternion base_quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	multi_body_->setBasePos(base_position);
	multi_body_->setWorldToBaseRot(base_quaternion);

	// �����N�̊������[�����g�v�Z
	float link_mass = 1.0f;
	btVector3 link_inertia(0.0f, 0.0f, 0.0f);
	temp_box = new btBoxShape(base_half_extents);
	temp_box->calculateLocalInertia(link_mass, link_inertia);
	delete temp_box;

	// �e�Ƃ�Link���W���玩���̃����N���W�܂ł̃x�N�g��
	btVector3 parent_comp_to_current_comp(0.0f, -base_half_extents.getY() * 2.0f, 0.0f);

	// �����̏d�S���玩���̃����N���W�܂ł̃x�N�g��
	btVector3 current_pivot_to_current_comp(0.0f, -base_half_extents.getY(), 0.0f);

	// �e�Ƃ�Link���W���玩���̏d�S�܂ł̃x�N�g��
	btVector3 parent_comp_to_current_pivot = parent_comp_to_current_comp - current_pivot_to_current_comp;

	// 3DoF���`�Ń����N��ݒ�
	for (int i = 0; i < link_num; i++)
	{
		multi_body_->setupSpherical(i, link_mass, link_inertia, i - 1,
									btQuaternion(0.0f, 0.0f, 0.0f, 1.0f),
									parent_comp_to_current_pivot,
									current_pivot_to_current_comp, true);
	}
	multi_body_->finalizeMultiDof();

	// �o�^
	((btMultiBodyDynamicsWorld*)dynamics_world_)->addMultiBody(multi_body_);

	// �}���`�{�f�B�̊e��t���O
	multi_body_->setCanSleep(can_sleep);
	multi_body_->setHasSelfCollision(true);
	multi_body_->setUseGyroTerm(true);

	// ���C
	multi_body_->setLinearDamping(0.1f);
	multi_body_->setAngularDamping(0.9f);

	// �q���ڂ̊p�x��ς���
	if (link_num > 0)
	{
		btScalar q1 = 90.0f * SIMD_PI / 180.0f;
		btQuaternion quaternion1(btVector3(0.0f, 0.0f, 1.0f).normalized(), q1);
		quaternion1.normalized();
		multi_body_->setJointPosMultiDof(0, quaternion1);
	}

	// �S�I�u�W�F�N�g�̃N�H�[�^�j�I��
	btAlignedObjectArray<btQuaternion> world_to_local;
	world_to_local.resize(multi_body_->getNumLinks() + 1);

	// �S�I�u�W�F�N�g�̕��s�ړ�
	btAlignedObjectArray<btVector3> local_origin;
	local_origin.resize(multi_body_->getNumLinks() + 1);

	// �x�[�X�I�u�W�F�N�g�̐ݒ�
	world_to_local[0] = multi_body_->getWorldToBaseRot();
	local_origin[0] = multi_body_->getBasePos();

	// �x�[�X�N�H�[�^�j�I���̋t���擾
	btScalar quat[4] = {-world_to_local[0].getX(), -world_to_local[0].getY(),
	-world_to_local[0].getZ(), world_to_local[0].getW()};

	// �x�[�X�I�u�W�F�N�g�̐���
	temp_box = new btBoxShape(base_half_extents);
	multi_shape_.push_back(temp_box);

	// �x�[�X�I�u�W�F�N�g�̃����N�R���_�[�쐬
	btMultiBodyLinkCollider* temp_link_collider = new btMultiBodyLinkCollider(multi_body_, -1);
	temp_link_collider->setCollisionShape(temp_box);
	btTransform base_transform;
	base_transform.setIdentity();
	base_transform.setOrigin(local_origin[0]);
	base_transform.setRotation(btQuaternion(quat[0], quat[1], quat[2], quat[3]));
	temp_link_collider->setWorldTransform(base_transform);
	temp_link_collider->setFriction(1.0f);
	multi_body_->setBaseCollider(temp_link_collider);
	dynamics_world_->addCollisionObject(temp_link_collider, 2, 1 + 2);
	link_collider_.push_back(temp_link_collider);


	// �����N��I�u�W�F�N�g�̃N�H�[�^�j�I���ƕ��s�ړ����v�Z
	for (int i = 0; i < multi_body_->getNumLinks(); i++)
	{
		const int paretn = multi_body_->getParent(i);
		world_to_local[i + 1] = multi_body_->getParentToLocalRot(i)
			* world_to_local[paretn + 1];
		local_origin[i + 1] = local_origin[paretn + 1] + (quatRotate(world_to_local[i + 1].inverse(),
																	 multi_body_->getRVector(i)));
	}

	// �����N��I�u�W�F�N�g�̐���
	btVector3 link_half_extents(0.05f, 0.37f, 0.1f);
	for (int i = 0; i < multi_body_->getNumLinks(); i++)
	{
		btVector3 link_object_position = local_origin[i + 1];
		btScalar quat2[4] = {-world_to_local[i + 1].getX(), -world_to_local[i + 1].getY(),
			-world_to_local[i + 1].getZ(), world_to_local[i + 1].getW()};

		temp_box = new btBoxShape(link_half_extents);
		multi_shape_.push_back(temp_box);
		temp_link_collider = new btMultiBodyLinkCollider(multi_body_, i);
		temp_link_collider->setCollisionShape(temp_box);

		btTransform link_transform;
		link_transform.setIdentity();
		link_transform.setOrigin(link_object_position);
		link_transform.setRotation(btQuaternion(quat2[0], quat2[1], quat2[2], quat2[3]));
		temp_link_collider->setWorldTransform(link_transform);
		temp_link_collider->setFriction(1.0f);
		multi_body_->getLink(i).m_collider = temp_link_collider;
		dynamics_world_->addCollisionObject(temp_link_collider, 2, 1 + 2);
		link_collider_.push_back(temp_link_collider);
	}
	*/
}



void BulletPhysicsManager::Uninit()
{
	dynamics_world_->setDebugDrawer(nullptr);
	for (auto& contents : constraint_)
	{
		if (contents == nullptr) continue;
		dynamics_world_->removeConstraint(contents);
	}
	SafeRelease::Normal(&dynamics_world_);

	for (auto& contents : rigid_body_)
	{
		SafeRelease::Normal(&contents);
	}
	for (auto& contents : motion_state_)
	{
		SafeRelease::Normal(&contents);
	}
	for (auto& contents : shape_)
	{
		SafeRelease::Normal(&contents);
	}

	//SafeRelease::Normal(&multi_body_);
	//for (auto& contents : link_collider_)
	//{
	//	SafeRelease::Normal(&contents);
	//}
	//for (auto& contents : multi_shape_)
	//{
	//	SafeRelease::Normal(&contents);
	//}

	for (auto& contents : constraint_)
	{
		SafeRelease::Normal(&contents);
	}
	for (auto& contents : constraint_rigid_body_)
	{
		SafeRelease::Normal(&contents);
	}
	for (auto& contents : constraint_motion_state_)
	{
		SafeRelease::Normal(&contents);
	}
	for (auto& contents : constraint_shape_)
	{
		SafeRelease::Normal(&contents);
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
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_A))
	{
		constraint_rigid_body_[0]->activate();
		constraint_rigid_body_[0]->applyCentralImpulse(btVector3(0.0f, 10.0f, 0.0f));
	}

	constraint_rigid_body_[0]->activate();
	constraint_rigid_body_[0]->applyForce(btVector3(0.0f, 40.0f, 0.0f), btVector3(0.0f, 1.0f, 0.0f));

	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_D))
	{
		dynamics_world_->removeConstraint(constraint_[constraint_.size() - 1]);
		SafeRelease::Normal(&constraint_[constraint_.size() - 1]);
		//constraint_rigid_body_[3]->applyCentralForce(btVector3(0.0f, 70.0f, 0.0f));
	}
	dynamics_world_->stepSimulation(TIME_STEP, MAX_SUB_STEP);
}



void BulletPhysicsManager::DrawDebug(Camera* camera)
{
	debug_->DrawSettingBefore(camera);
	dynamics_world_->debugDrawWorld();
	debug_->DrawSettingAfter();
}