//================================================================================
//!	@file	 StartBlock.cpp
//!	@brief	 �X�^�[�g�u���b�NClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StartBlock.h"



//****************************************
// �v���p�e�B��`
//****************************************
void StartBlock::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}



//****************************************
// �֐���`
//****************************************
void StartBlock::Init(DrawBase* draw, CollisionBase* collision)
{
	// ���N���X�̏�����
	GameObjectBase::Init(nullptr, draw, collision);
}