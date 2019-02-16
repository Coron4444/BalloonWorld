//================================================================================
//!	@file	 AABB.cpp
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../AABB.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* AABB::getpPosition()
{ 
	return &position_; 
}



Vector3D* AABB::getpLength()
{ 
	return &length_; 
}



void AABB::setLength(Vector3D value)
{ 
	length_ = value; 
};



//****************************************
// 関数定義
//****************************************
AABB::~AABB()
{

}



void AABB::Init(Vector3D position, Vector3D length)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::AABB);

	position_ = position;
	length_ = length;

	CalculationMinAndMax();
}



void AABB::Update()
{
	CalculationMinAndMax();
}



void AABB::CalculationMinAndMax()
{
	*getpMax() = position_ + length_;
	*getpMin() = position_ - length_;
}