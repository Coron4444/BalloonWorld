//================================================================================
//!	@file	 CollisionShapeBase.cpp
//!	@brief	 �Փˌ`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionShapeBase.h"



//****************************************
// �v���p�e�B��`
//****************************************
CollisionShapeBase::Type CollisionShapeBase::getType()
{
	return type_; 
}



//****************************************
// �֐���`
//****************************************
CollisionShapeBase::CollisionShapeBase(Type type) 
	: type_(type) 
{
}



CollisionShapeBase::~CollisionShapeBase()
{
}