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



BulletPhysicsObject* BulletPhysicsManager::getpObjectSphere(float mass, Vec3 inertia,
															Vec3 position,
															Quaternion quaternion,
															float radius)
{
	// 新規作成
	BulletPhysicsObject* object = new BulletPhysicsObject();
	object->InitSphere(mass, &inertia, &position, &quaternion, radius);
	object->AddReferenceCounter();
	object_.push_back(object);
	dynamics_world_->addRigidBody(object->getpRigidBody());
	return object;
}



BulletPhysicsObject* BulletPhysicsManager::getpObjectOBB(float mass, Vec3 inertia,
														 Vec3 position,
														 Quaternion quaternion,
														 Vec3 edge_half_length)
{
	// 新規作成
	BulletPhysicsObject* object = new BulletPhysicsObject();
	object->InitOBB(mass, &inertia, &position, &quaternion, &edge_half_length);
	object->AddReferenceCounter();
	object_.push_back(object);
	dynamics_world_->addRigidBody(object->getpRigidBody());
	return object;
}



BulletPhysicsObject* BulletPhysicsManager::getpObjectCapsule(float mass, Vec3 inertia, Vec3 position,
															 Quaternion quaternion, float radius, float height)
{
	// 新規作成
	BulletPhysicsObject* object = new BulletPhysicsObject();
	object->InitCapsule(mass, &inertia, &position, &quaternion, radius, height);
	object->AddReferenceCounter();
	object_.push_back(object);
	dynamics_world_->addRigidBody(object->getpRigidBody());
	return object;
}



BulletPhysicsConstraint* BulletPhysicsManager::setConstraintPointToPoint(BulletPhysicsObject* bullet_object0,
																		 BulletPhysicsObject* bullet_object1,
																		 Vec3 point0, Vec3 point1)
{
	// 新規作成
	BulletPhysicsConstraint* constraint = new BulletPhysicsConstraint();
	constraint->InitPointToPoint(bullet_object0->getpRigidBody(),
								 bullet_object1->getpRigidBody(),
								 &point0, &point1);

	constraint->AddReferenceCounter();
	constraint_.push_back(constraint);
	dynamics_world_->addConstraint(constraint->getpConstraint());
	return constraint;
}



BulletPhysicsConstraint* BulletPhysicsManager::setConstraintHinge(BulletPhysicsObject* bullet_object0,
																  BulletPhysicsObject* bullet_object1,
																  Vec3 point0, Vec3 point1,
																  float angle_min, float angle_max,
																  Vec3 axis)
{
	// 新規作成
	BulletPhysicsConstraint* constraint = new BulletPhysicsConstraint();
	constraint->InitHinge(bullet_object0->getpRigidBody(),
						  bullet_object1->getpRigidBody(),
						  &point0, &point1, angle_min, angle_max, &axis);

	constraint->AddReferenceCounter();
	constraint_.push_back(constraint);
	dynamics_world_->addConstraint(constraint->getpConstraint());
	return constraint;
}



BulletPhysicsConstraint* BulletPhysicsManager::setConstraintUniversal(BulletPhysicsObject* bullet_object0,
																	  BulletPhysicsObject* bullet_object1,
																	  Vec3 anchor,
																	  float angle_min0, float angle_min1,
																	  float angle_max0, float angle_max1,
																	  Vec3 axis0, Vec3 axis1)
{
	// 新規作成
	BulletPhysicsConstraint* constraint = new BulletPhysicsConstraint();
	constraint->InitUniversal(bullet_object0->getpRigidBody(),
							  bullet_object1->getpRigidBody(),
							  &anchor, angle_min0, angle_min1,
							  angle_max0, angle_max1, &axis0, &axis1);

	constraint->AddReferenceCounter();
	constraint_.push_back(constraint);
	dynamics_world_->addConstraint(constraint->getpConstraint());
	return constraint;
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
}



void BulletPhysicsManager::Uninit()
{
	// 拘束の解放
	auto iterator2 = constraint_.begin();
	while (iterator2 != constraint_.end())
	{
		(*iterator2)->ForcedRelease();
		iterator2 = constraint_.begin();
	}
	constraint_.clear();

	// ワールドの解放
	dynamics_world_->setDebugDrawer(nullptr);
	SafeRelease::Normal(&dynamics_world_);

	// オブジェクトの解放
	auto iterator = object_.begin();
	while (iterator != object_.end())
	{
		(*iterator)->ForcedRelease();
		iterator = object_.begin();
	}
	object_.clear();

	// その他解放
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



void BulletPhysicsManager::ReleaseFromTheObjectList(BulletPhysicsObject* object)
{
	for (auto iterator = object_.begin(); iterator != object_.end(); iterator++)
	{
		if (*iterator != object) continue;
		object_.erase(iterator);
		break;
	}
}



void BulletPhysicsManager::ReleaseFromTheConstraintList(BulletPhysicsConstraint* constraint)
{
	for (auto iterator = constraint_.begin(); iterator != constraint_.end(); iterator++)
	{
		if (*iterator != constraint) continue;
		dynamics_world_->removeConstraint(constraint->getpConstraint());
		constraint_.erase(iterator);
		break;
	}
}