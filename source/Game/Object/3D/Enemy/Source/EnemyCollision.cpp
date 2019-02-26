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
const Vector3D EnemyCollision::MAIN_OBB_LENGTH(1.0f, 1.0f, 1.0f);



//****************************************
// 関数定義
//****************************************
void EnemyCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::ENEMY);

	// 衝突オブジェクト作成
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// メインOBBの作成
	main_obb_ = new OBB();
	main_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(MAIN_OBB_LENGTH));
	collision_object_->AddShape((int)ShapeTag::MAIN, main_obb_);
}



void EnemyCollision::Update()
{
	// メインOBBの更新
	*main_obb_->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	main_obb_->RotationMatrix(getpGameObject()->getpTransform()->getpNoInitRotationMatrix());
	main_obb_->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * MAIN_OBB_LENGTH.x;
	main_obb_->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * MAIN_OBB_LENGTH.y;
	main_obb_->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * MAIN_OBB_LENGTH.z;
}