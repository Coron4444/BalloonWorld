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
	CollisionBase::setType(CollisionBase::Type::GOAL);

	// 衝突オブジェクト作成
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// メイン球の作成
	main_sphere_ = new Sphere();
	main_sphere_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					   MAIN_SPHERE_RADIUS);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void GoalCollision::Update()
{
	// メイン球の更新
	*main_sphere_->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}