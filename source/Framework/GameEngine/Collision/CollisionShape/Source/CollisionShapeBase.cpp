//================================================================================
//!	@file	 CollisionShapeBase.cpp
//!	@brief	 �Փˌ`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"



//****************************************
// �v���p�e�B��`
//****************************************
CollisionShapeBase::Type CollisionShapeBase::getType()
{
	return type_; 
}



void CollisionShapeBase::setType(CollisionShapeBase::Type value)
{
	type_ = value;
}



Vector3D* CollisionShapeBase::getpMax()
{
	return &max_;
}



Vector3D* CollisionShapeBase::getpMin()
{

	return &min_;
}



//****************************************
// �֐���`
//****************************************
CollisionShapeBase::~CollisionShapeBase()
{
}