//================================================================================
//!	@file	 CollisionShapeBase.cpp
//!	@brief	 衝突形状BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CollisionShapeBase.h"



//****************************************
// プロパティ定義
//****************************************
CollisionShapeBase::Type CollisionShapeBase::getType()
{
	return type_; 
}



void CollisionShapeBase::setType(CollisionShapeBase::Type value)
{
	type_ = value;
}



Vector3D* CollisionShapeBase::getpMax()
{
	return &max_;
}



Vector3D* CollisionShapeBase::getpMin()
{

	return &min_;
}



//****************************************
// 関数定義
//****************************************
CollisionShapeBase::~CollisionShapeBase()
{
}