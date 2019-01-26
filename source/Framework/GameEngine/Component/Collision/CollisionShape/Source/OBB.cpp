//================================================================================
//!	@file	 OBB.cpp
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "OBB.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* OBB::getpPosition()
{
	return &position_; 
}



Vector3D* OBB::getpLength()
{ 
	return &length_; 
}



AxisVector* OBB::getpAxisVector()
{ 
	return &axis_; 
}



Vector3D OBB::getRightVector()
{
	math_vector_ = *axis_.GetRight();
	math_vector_.AnyLengthVector(length_.x);
	return math_vector_;
}



Vector3D OBB::getUpVector()
{
	math_vector_ = *axis_.GetUp();
	math_vector_.AnyLengthVector(length_.y);
	return math_vector_;
}



Vector3D OBB::getForwardVector()
{
	math_vector_ = *axis_.GetForawrd();
	math_vector_.AnyLengthVector(length_.z);
	return math_vector_;
}



Vector3D OBB::getRightVectorHalf()
{
	return getRightVector() / 2;
}



Vector3D OBB::getUpVectorHalf()
{
	return getUpVector() / 2;
}



Vector3D OBB::getForwardVectorHalf()
{
	return getForwardVector() / 2;
}



//****************************************
// �֐���`
//****************************************
OBB::OBB()
	: CollisionShapeBase(CollisionShapeBase::Type::OBB)
{
}



void OBB::Init(Vector3D position, Vector3D length)
{
	// ���W��ݒ�
	position_ = position;

	// ������ݒ�
	length_ = length;
}