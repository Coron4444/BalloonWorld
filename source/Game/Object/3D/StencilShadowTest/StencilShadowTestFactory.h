//================================================================================
//!	@file	 StencilShadowTestFactory.h
//!	@brief	 �X�e���V���V���h�E�e�X�g����Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_STENCIL_SHADOW_TEST_FACTORY_H_
#define _STENCIL_SHADOW_TEST_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "StencilShadowTest.h"
#include "StencilShadowTestDraw.h"



//************************************************************														   
//! @brief   �X�e���V���V���h�E�e�X�g����Class
//!
//! @details �X�e���V���V���h�E�e�X�g�̐���Class
//************************************************************
class StencilShadowTestFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �X�e���V���V���h�E�e�X�g�����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval StencilShadowTest* �X�e���V���V���h�E�e�X�g
	//----------------------------------------
	StencilShadowTest* Create();
};



#endif