//================================================================================
//!	@file	 Triangle.cpp
//!	@brief	 �O�p�`����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Triangle.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* Triangle::getpPoint0()
{
	return &point0_; 
}



Vector3D* Triangle::getpPoint1()
{
	return &point1_;
}



Vector3D* Triangle::getpPoint2()
{
	return &point2_;
}



Plane* Triangle::getpPlane()
{
	return &plane_; 
}



//****************************************
// �֐���`
//****************************************
Triangle::Triangle()
	: CollisionShapeBase(CollisionShapeBase::Type::TRIANGLE)
{
}



void Triangle::Init(Vec3 point0, Vec3 point1, Vec3 point2)
{
	// 3�_
	point0_ = point0;
	point1_ = point1;
	point2_ = point2;

	// ����
	plane_.Init(point0, point1, point2);
}