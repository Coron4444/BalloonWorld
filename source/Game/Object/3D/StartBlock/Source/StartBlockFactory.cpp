//================================================================================
//!	@file	 StartBlockFactory.cpp
//!	@brief	 �X�^�[�g�u���b�N����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StartBlockFactory.h"



//****************************************
// �֐���`
//****************************************
StartBlock* StartBlockFactory::Create()
{
	StartBlock* temp = new StartBlock();
	temp->Init(new StartBlockDraw(),
			   new StartBlockCollision());
	return temp;
}