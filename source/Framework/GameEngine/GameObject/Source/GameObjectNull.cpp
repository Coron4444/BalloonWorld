//================================================================================
//!	@file	 GameObjectNull.cpp
//!	@brief	 �Q�[���I�u�W�F�N�g��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/30
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameObjectNull.h"



//****************************************
// �֐���`
//****************************************
GameObjectNull::GameObjectNull(bool is_registration)
	: GameObjectBase(is_registration)
{
}



GameObjectNull::~GameObjectNull()
{
}



void GameObjectNull::Uninit()
{
	// ���N���X�̏I������
	GameObjectBase::Uninit();
}

void GameObjectNull::Reset()
{
	// ���N���X�̃��Z�b�g����
	GameObjectBase::Reset();
}