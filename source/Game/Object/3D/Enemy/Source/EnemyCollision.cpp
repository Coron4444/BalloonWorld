//================================================================================
//!	@file	 EnemyCollision.cpp
//!	@brief	 敵衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../EnemyCollision.h"
#include "../Enemy.h"



//****************************************
// 定数定義
//****************************************
const float EnemyCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float EnemyCollision::SUBSTANCE_SPHERE_RADIUS = 1.0f;



//****************************************
// 関数定義
//****************************************
void EnemyCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::ENEMY);

	// 衝突オブジェクト群作成
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// バウンディング球の作成
	Sphere* temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  BOUNDING_SPHERE_RADIUS);
	bounding_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::BOUNDING_SPHERE);
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);

	// 本体球の作成
	temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  SUBSTANCE_SPHERE_RADIUS);
	substance_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::SUBSTANCE_SPHERE);
	collision_objects_->AddCollisionObjectToArray(substance_sphere_);
}



void EnemyCollision::Update()
{
	// 衝突オブジェクト群更新
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// バウンディング球の更新
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();

	// 本体球の更新
	temp_sphere = (Sphere*)substance_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}