//================================================================================
//!	@file	 GoalCollision.cpp
//!	@brief	 ゴール衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../GoalCollision.h"
#include "../Goal.h"



//****************************************
// 定数定義
//****************************************
const float GoalCollision::MAIN_SPHERE_RADIUS = 1.0f;



//****************************************
// 関数定義
//****************************************
void GoalCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::ENEMY);

	// 衝突オブジェクト作成
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// メイン球の作成
	main_sphere_ = new Sphere();
	main_sphere_->Init(MAIN_SPHERE_RADIUS);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_obb_);

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



void GoalCollision::Update()
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