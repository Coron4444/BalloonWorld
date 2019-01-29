//================================================================================
//!	@file	 OBB.cpp
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../OBB.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* OBB::getpPosition()
{
	return &position_; 
}



Vector3D* OBB::getpLength()
{ 
	return &length_; 
}



Axis* OBB::getpAxis()
{ 
	return &axis_; 
}



Vector3D OBB::getRight()
{
	math_vector_ = *axis_.getpRight();
	math_vector_.ChangeAnyLength(length_.x);
	return math_vector_;
}



Vector3D OBB::getUp()
{
	math_vector_ = *axis_.getpUp();
	math_vector_.ChangeAnyLength(length_.y);
	return math_vector_;
}



Vector3D OBB::getForward()
{
	math_vector_ = *axis_.getpForawrd();
	math_vector_.ChangeAnyLength(length_.z);
	return math_vector_;
}



Vector3D OBB::getRightHalf()
{
	return getRight() / 2;
}



Vector3D OBB::getUpHalf()
{
	return getUp() / 2;
}



Vector3D OBB::getForwardHalf()
{
	return getForward() / 2;
}



//****************************************
// 関数定義
//****************************************
OBB::OBB()
	: CollisionShapeBase(CollisionShapeBase::Type::OBB)
{
}



void OBB::Init(Vector3D position, Vector3D length)
{
	// 座標を設定
	position_ = position;

	// 長さを設定
	length_ = length;
}