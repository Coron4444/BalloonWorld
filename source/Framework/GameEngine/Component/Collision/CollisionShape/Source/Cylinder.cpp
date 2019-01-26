//================================================================================
//!	@file	 Cylinder.cpp
//!	@brief	 �~��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Cylinder.h"



//****************************************
// �v���p�e�B��`
//****************************************
LineSegment* Cylinder::getpLineSegment()
{ 
	return &line_segment_; 
}



Vector3D* Cylinder::getpPosition()
{
	return line_segment_.getpPosition(); 
}



Vector3D* Cylinder::getpVector()
{ 
	return line_segment_.getpVector();
}



Vector3D Cylinder::getAddVectorToPosition()
{ 
	return line_segment_.getAddVectorToPosition(); 
}



float Cylinder::getRadius()
{ 
	return radius_;
}



void Cylinder::setRadius(float value)
{ 
	radius_ = value; 
}



//****************************************
// �֐���`
//****************************************
Cylinder::Cylinder() 
	: CollisionShapeBase(CollisionShapeBase::Type::CYLINDER) 
{
}



void Cylinder::Init(Vector3D position, Vector3D vector, float radius)
{
	// ����
	line_segment_.Init(position, vector);

	// ���a
	radius_ = radius;
}