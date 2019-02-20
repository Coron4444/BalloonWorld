//================================================================================
//!	@file	 NeedleFactory.h
//!	@brief	 ������Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_NEEDLE_FACTORY_H_
#define _NEEDLE_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Needle.h"
#include "NeedleDraw.h"
#include "NeedleCollision.h"
#include "NeedleState_Loop.h"



//************************************************************														   
//! @brief   ������Class
//!
//! @details ���̐���Class
//************************************************************
class NeedleFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *state �X�e�[�g
	//! @retval Needle* ��
	//----------------------------------------
	Needle* Create(Needle::State* state);
};



#endif