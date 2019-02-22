//================================================================================
//!	@file	 StartBlock.cpp
//!	@brief	 スタートブロックClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StartBlock.h"


//****************************************
// プロパティ定義
//****************************************
const Vec3 StartBlock::SCALE(15.0f, 5.0f, 15.0f);
const float StartBlock::ROTATION_SPEED = 0.01f;



//****************************************
// プロパティ定義
//****************************************
void StartBlock::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}



//****************************************
// 関数定義
//****************************************
void StartBlock::Init(DrawBase* draw, CollisionBase* collision)
{
	// 変形
	*getpTransform()->getpScale() = SCALE;
	getpTransform()->CreateAxisAndWorldMatrix();

	// 基底クラスの初期化
	GameObjectBase::Init(draw, collision);
}



void StartBlock::Update()
{
	// 変形
	*getpTransform()->getpAngleYaw() += ROTATION_SPEED;
	getpTransform()->CreateAxisAndWorldMatrix();
}