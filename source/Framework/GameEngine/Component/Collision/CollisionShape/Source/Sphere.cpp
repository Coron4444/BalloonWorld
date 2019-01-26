//================================================================================
//!	@file	 Sphere.cpp
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Sphere.h"



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
Sphere::Sphere()
	: CollisionShapeBase(CollisionShapeBase::Type::SPHERE)
{
}



void Sphere::Init(Vector3D position, float radius)
{
	// ���W
	position_ = position;

	// ���a
	radius_ = radius;
}