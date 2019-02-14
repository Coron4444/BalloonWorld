//================================================================================
//!	@file	 Sphere.cpp
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Sphere.h"



//****************************************
// �v���p�e�B��`
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
// �֐���`
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