//================================================================================
//!	@file	 Sphere.cpp
//!	@brief	 球Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Sphere.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* Sphere::getpPosition() 
{
	return &position_; 
}



float Sphere::getRadius()
{ 
	return radius_; 
}



void Sphere::setRadius(float value)
{ 
	radius_ = value;
}



//****************************************
// 関数定義
//****************************************
Sphere::~Sphere()
{
}



void Sphere::Init(Vector3D position, float radius)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::CAPSULE);

	position_ = position;
	radius_ = radius;

	CalculationMinAndMax();
}



void Sphere::Update()
{
	CalculationMinAndMax();
}



void Sphere::CalculationMinAndMax()
{
	Vector3D length(1.0f, 1.0f, 1.0f);
	length.ChangeAnyLength(radius_);
	*getpMax() = position_ + length;
	*getpMin() = position_ + -length;
}