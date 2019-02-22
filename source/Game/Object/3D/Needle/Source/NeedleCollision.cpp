//================================================================================
//!	@file	 NeedleCollision.cpp
//!	@brief	 棘衝突Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../NeedleCollision.h"



//****************************************
// 定数定義
//****************************************
const float NeedleCollision::MAIN_SPHERE_RADIUS = 1.0f;



//****************************************
// 関数定義
//****************************************
void NeedleCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::NEEDLE);

	// 衝突オブジェクト作成
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// メイン球の作成
	main_sphere_ = new Sphere();
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	float radius = MAIN_SPHERE_RADIUS * getpGameObject()->getpTransform()->getpScale()->x;
	main_sphere_->Init(position, radius);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void NeedleCollision::Update()
{
	// メイン球の更新
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	float radius = MAIN_SPHERE_RADIUS * getpGameObject()->getpTransform()->getpScale()->x;
	*main_sphere_->getpPosition() = position;
	main_sphere_->setRadius(radius);
}