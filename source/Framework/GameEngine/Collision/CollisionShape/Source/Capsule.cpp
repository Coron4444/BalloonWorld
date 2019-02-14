//================================================================================
//!	@file	 Capsule.h
//!	@brief	 �J�v�Z��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Capsule.h"



//****************************************
// �v���p�e�B��`
//****************************************
Sphere* Capsule::getpSphere0() 
{ 
	return &sphere0_;
}



Sphere* Capsule::getpSphere1() 
{ 
	return &sphere1_; 
}



Cylinder* Capsule::getpCylinder() 
{
	return &cylinder_;
}



LineSegment* Capsule::getpLineSegment()
{ 
	return cylinder_.getpLineSegment();
}



Vector3D* Capsule::getpPosition() 
{
	return cylinder_.getpPosition();
}



Vector3D* Capsule::getpVector()
{ 
	return cylinder_.getpVector();
}



Vector3D Capsule::getAddVectorToPosition() 
{
	return cylinder_.getAddVectorToPosition(); 
}



float Capsule::getRadius() 
{ 
	return cylinder_.getRadius(); 
}



void Capsule::setRadius(float value) 
{ 
	cylinder_.setRadius(value); 
}



//****************************************
// �֐���`
//****************************************
Capsule::~Capsule()
{
}



void Capsule::Init(Vector3D position, Vector3D vector, float radius)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::CAPSULE);

	// �~��
	cylinder_.Init(position, vector, radius);

	// ��
	sphere0_.Init(*cylinder_.getpPosition(), radius);
	sphere1_.Init(cylinder_.getAddVectorToPosition(), radius);

	CalculationMinAndMax();
}



void Capsule::Update()
{
	// ���̍X�V
	*sphere0_.getpPosition() = *cylinder_.getpPosition();
	sphere0_.setRadius(cylinder_.getRadius());
	*sphere1_.getpPosition() = cylinder_.getAddVectorToPosition();
	sphere1_.setRadius(cylinder_.getRadius());

	// �ŏ��ő�X�V
	CalculationMinAndMax();
}



void Capsule::CalculationMinAndMax()
{
	Vector3D length(1.0f, 1.0f, 1.0f);
	length.ChangeAnyLength(sphere0_.getRadius());

	*getpMax() = *cylinder_.getpLineSegment()->getpMax() + length;
	*getpMin() = *cylinder_.getpLineSegment()->getpMin() + -length;
}