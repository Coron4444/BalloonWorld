//================================================================================
//!	@file	 StartBlockFactory.h
//!	@brief	 �X�^�[�g�u���b�N����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_START_BLOCK_FACTORY_H_
#define _START_BLOCK_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "StartBlock.h"
#include "StartBlockDraw.h"
#include "StartBlockCollision.h"



//************************************************************														   
//! @brief   �X�^�[�g�u���b�N����Class
//!
//! @details �X�^�[�g�u���b�N�̐���Class
//************************************************************
class StartBlockFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �X�^�[�g�u���b�N�����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval StartBlock* �X�^�[�g�u���b�N
	//----------------------------------------
	StartBlock* Create();
};



#endif