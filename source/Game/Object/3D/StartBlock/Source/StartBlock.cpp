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
	// 基底クラスの初期化
	GameObjectBase::Init(nullptr, draw, collision);
}