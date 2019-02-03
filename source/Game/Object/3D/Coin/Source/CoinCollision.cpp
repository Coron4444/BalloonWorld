//================================================================================
//!	@file	 CoinCollision.cpp
//!	@brief	 コイン衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CoinCollision.h"



//****************************************
// 定数定義
//****************************************
const Vec3 CoinCollision::BOUNDING_OBB_LENGTH(1.0f, 1.0f, 1.0f);
const Vec3 CoinCollision::SUBSTANCE_OBB_LENGTH(1.0f, 1.0f, 1.0f);



//****************************************
// 関数定義
//****************************************
void CoinCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::COIN);

	// 衝突オブジェクト群作成
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// バウンディングOBBの作成
	OBB* temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(BOUNDING_OBB_LENGTH));

	bounding_obb_ = new CollisionObject(temp_obb_, (int)ObjectTag::BOUNDING_OBB);
	collision_objects_->AddCollisionObjectToArray(bounding_obb_);

	// 実体OBBの作成
	temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(SUBSTANCE_OBB_LENGTH));
	substance_obb_ = new CollisionObject(temp_obb_, (int)ObjectTag::SUBSTANCE_OBB);
	collision_objects_->AddCollisionObjectToArray(substance_obb_);
}



void CoinCollision::Update()
{
	// 衝突オブジェクト群更新
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// バウンディングOBBの更新
	OBB* temp_obb = (OBB*)bounding_obb_->getpCollisionShape();
	*temp_obb->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*temp_obb->getpAxis() = *getpGameObject()->getpTransform()->getpAxis();
	temp_obb->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * BOUNDING_OBB_LENGTH.x;
	temp_obb->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * BOUNDING_OBB_LENGTH.y;
	temp_obb->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * BOUNDING_OBB_LENGTH.z;


	// 本体スフィアOBBの更新
	temp_obb = (OBB*)substance_obb_->getpCollisionShape();
	*temp_obb->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*temp_obb->getpAxis() = *getpGameObject()->getpTransform()->getpAxis();
	temp_obb->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * SUBSTANCE_OBB_LENGTH.x;
	temp_obb->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * SUBSTANCE_OBB_LENGTH.y;
	temp_obb->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * SUBSTANCE_OBB_LENGTH.z;
}