//================================================================================
//!	@file	 AABB.cpp
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "AABB.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* AABB::getpPositon()
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



Vector3D* AABB::getpMin()
{ 
	return &min_; 
}



Vector3D* AABB::getpMax()
{ 
	return &max_; 
}



//****************************************
// �֐���`
//****************************************
AABB::AABB() 
	: CollisionShapeBase(CollisionShapeBase::Type::AABB) 
{
}



void AABB::Init(Vector3D position, Vector3D length)
{
	// ���W��ݒ�
	position_ = position;

	// ������ݒ�
	length_ = length;

	// �ŏ��l�ƍő�l
	UpdateMinAndMax();
}



void AABB::Update()
{
	// �ŏ��l�ƍő�l
	UpdateMinAndMax();
}



void AABB::UpdateMinAndMax()
{
	min_ = position_ - length_;
	max_ = position_ + length_;
}