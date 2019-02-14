//================================================================================
//!	@file	 Plane.cpp
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Plane.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* Plane::getpNormal()
{ 
	return &normal_; 
}



float Plane::getAdjustmetD()
{ 
	return adjustmet_d_; 
}



//****************************************
// �֐���`
//****************************************
Plane::~Plane()
{
}



void Plane::Init(Vector3D normal, Vector3D point)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::CAPSULE);

	// �@��
	normal_ = normal;
	normal_.ChangeNormalize();

	// D����
	adjustmet_d_ = -((normal_.x * point.x) + (normal_.y * point.y) 
					 + (normal_.z * point.z));
}



void Plane::Init(Vec3 point0, Vec3 point1, Vec3 point2)
{
	// �@���̍쐬
	Vec3 temp_normal_vector = Vector3D::CreateCrossPoint3(&point0, &point1, &point2);

	// ������
	Init(temp_normal_vector, point0);

	CalculationMinAndMax();
}



void Plane::Update()
{
}



void Plane::CalculationMinAndMax()
{
}