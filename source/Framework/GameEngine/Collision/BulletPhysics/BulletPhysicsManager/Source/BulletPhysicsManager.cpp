//================================================================================
//!	@file	 BulletPhysicsManager.cpp
//!	@brief	 バレットフィジックスマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BulletPhysicsManager.h"
#include "../../BulletPhysicsDebug.h"
#include "../../BulletPhysicsObject.h"


#include <Tool/SafeRelease.h>
#include <GameEngine/Input/InputManager/InputManager.h>


//****************************************
// 定数定義
//****************************************
const btVector3 BulletPhysicsManager::DEFULT_GRAVITY(0.0f, -9.8f, 0.0f);
const btScalar BulletPhysicsManager::TIME_STEP = 1.0f / 60.0f;
const int BulletPhysicsManager::MAX_SUB_STEP = 10;



//****************************************
// static変数定義
//****************************************
BulletPhysicsManager* BulletPhysicsManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
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
// static関数定義
//****************************************
void BulletPhysicsManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
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



//****************************************
// 関数定義
//****************************************
BulletPhysicsManager::BulletPhysicsManager()
{
}



void BulletPhysicsManager::Init()
{
	// 衝突計算の設定(今回はデフォルトを使用)
	configuration_ = new btDefaultCollisionConfiguration();
	dispatcher_ = new btCollisionDispatcher(configuration_);

	// ブロードフェーズ法(衝突する可能性のあるオブジェクトの検出)の設定(今回はOctree)
	broadphase_ = new btDbvtBroadphase();

	// 拘束ソルバ設定(オブジェクトの重なり解消などの設定)
	solver_ = new btSequentialImpulseConstraintSolver();

	// bulletワールド設定
	dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, solver_, configuration_);
	dynamics_world_->setGravity(DEFULT_GRAVITY);

	// デバッグ初期化
	debug_ = new BulletPhysicsDebug();
	debug_->Init();
	dynamics_world_->setDebugDrawer(debug_);

	// 地面
	BulletPhysicsObject* temp_object = new BulletPhysicsObject();
	temp_object->InitOBB(0.0f, btVector3(0.0f, 0.0f, 0.0f),
						 btVector3(0.0f, -50.0f, 0.0f), btQuaternion(0, 0, 0, 1),
						 btVector3(50.0f, 50.0f, 50.0f));
	temp_object->getpRigidBody()->setRestitution(0.5f);
	dynamics_world_->addRigidBody(temp_object->getpRigidBody());
	object_.push_back(temp_object);

	// 球
	temp_object = new BulletPhysicsObject();
	temp_object->InitSphere(20.0f, btVector3(0.0f, 0.0f, 0.0f),
							btVector3(0.0f, 10.0f, 0.0f), btQuaternion(0, 0, 0, 1),
							1.0f);
	temp_object->getpRigidBody()->setRestitution(1.0f);
	temp_object->getpRigidBody()->setRollingFriction(0.1f);
	temp_object->getpRigidBody()->setSpinningFriction(0.1f);
	dynamics_world_->addRigidBody(temp_object->getpRigidBody());
	object_.push_back(temp_object);

	// 球2
	temp_object = new BulletPhysicsObject();
	temp_object->InitSphere(20.0f, btVector3(0.0f, 0.0f, 0.0f),
							btVector3(1.0f, 1.0f, 0.0f), btQuaternion(0, 0, 0, 1),
							1.0f);
	temp_object->getpRigidBody()->setRestitution(1.0f);
	temp_object->getpRigidBody()->setRollingFriction(0.1f);
	temp_object->getpRigidBody()->setSpinningFriction(0.1f);
	dynamics_world_->addRigidBody(temp_object->getpRigidBody());
	object_.push_back(temp_object);

	// 形状の組み合わせ
	comp_ = new btCompoundShape();
	btScalar mass = 1.0f;
	btVector3 inertia = btVector3(0.0f, 0.0f, 0.0f);
	comp_->calculateLocalInertia(mass, inertia);

	comp_shape_[0] = new btCapsuleShape(1.0f, 3.0f);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));		// 平行移動
	transform.setRotation(btQuaternion(0, 1, 0, 1));
	comp_->addChildShape(transform, comp_shape_[0]);

	comp_shape_[1] = new btBoxShape(btVector3(1.0f, 1.0f, 3.0f));
	transform.setIdentity();
	transform.setOrigin(btVector3(2.0f, 2.0f, 0.0f));		// 平行移動
	transform.setRotation(btQuaternion(0, 1, 0, 1));
	comp_->addChildShape(transform, comp_shape_[1]);

	transform.setIdentity();
	transform.setOrigin(btVector3(2.0f, 10.0f, 0.0f));		// 平行移動
	transform.setRotation(btQuaternion(0, 0, 0, 1));
	comp_motion_state_ = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, comp_motion_state_,
															comp_, inertia);
	comp_rigid_body_ = new btRigidBody(rigidbody_info);
	comp_rigid_body_->setRestitution(1.0f);
	comp_rigid_body_->setRollingFriction(0.1f);
	comp_rigid_body_->setSpinningFriction(0.1f);
	comp_rigid_body_->setDamping(0.7f, 1.0f);
	comp_rigid_body_->setAnisotropicFriction(comp_->getAnisotropicRollingFrictionDirection(),
											 btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);
	dynamics_world_->addRigidBody(comp_rigid_body_);



	// 拘束
	btVector3 box_half(0.05f, 0.37f, 0.1f);
	btCollisionShape* temp_shape;
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
		transform.setOrigin(btVector3(0.0f, 6.0f - box_half.getY() * 2 * i, 0.0f));		// 平行移動
		transform.setRotation(btQuaternion(0, 0, 0, 1));
		btDefaultMotionState* temp_motion_state = new btDefaultMotionState(transform);
		constraint_motion_state_.push_back(temp_motion_state);

		rigidbody_info = btRigidBody::btRigidBodyConstructionInfo(mass, temp_motion_state,
																  temp_shape, inertia);
		btRigidBody* temp_rigid_body = new btRigidBody(rigidbody_info);
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
											 *(*object_.begin())->getpRigidBody(),
											 btVector3(0.0f, -box_half.getY(), 0.0f),
											 btVector3(0.0f, 50.0f, 0.0f));
	dynamics_world_->addConstraint(temp_const);
	constraint_.push_back(temp_const);

}



void BulletPhysicsManager::Uninit()
{
	// ワールドの解放
	dynamics_world_->setDebugDrawer(nullptr);
	for (auto& contents : constraint_)
	{
		if (contents == nullptr) continue;
		dynamics_world_->removeConstraint(contents);
	}
	SafeRelease::Normal(&dynamics_world_);

	// オブジェクトの解放
	auto iterator = object_.begin();
	while (iterator != object_.end())
	{
		(*iterator)->ForcedRelease();
		iterator = object_.begin();
	}
	object_.clear();

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

	// その他解放
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



void BulletPhysicsManager::ReleaseFromTheList(BulletPhysicsObject* object)
{
	for (auto iterator = object_.begin(); iterator != object_.end(); iterator++)
	{
		if (*iterator != object) continue;
		object_.erase(iterator);
		break;
	}
}