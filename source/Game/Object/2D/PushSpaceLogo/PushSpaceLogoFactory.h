//================================================================================
//!	@file	 PushSpaceLogoFactory.h
//!	@brief	 �v�b�V���X�y�[�X���S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_PUSH_SPACE_LOGO_FACTORY_H_
#define _PUSH_SPACE_LOGO_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "PushSpaceLogo.h"
#include "PushSpaceLogoUpdate.h"
#include "PushSpaceLogoDraw.h"



//************************************************************														   
//! @brief   �v�b�V���X�y�[�X���S����Class
//!
//! @details �v�b�V���X�y�[�X���S�̐���Class
//************************************************************
class PushSpaceLogoFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �v�b�V���X�y�[�X���S�����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval PushSpaceLogo* �v�b�V���X�y�[�X���S
	//----------------------------------------
	PushSpaceLogo* Create();
};



#endif