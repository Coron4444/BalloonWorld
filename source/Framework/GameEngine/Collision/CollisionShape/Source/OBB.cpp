//================================================================================
//!	@file	 OBB.cpp
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../OBB.h"



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