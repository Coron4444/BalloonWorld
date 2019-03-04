//================================================================================
//!	@file	 StencilShadowTest.h
//!	@brief	 �X�e���V���V���h�E�e�X�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_STENCIL_SHADOW_TEST_H_
#define _STENCIL_SHADOW_TEST_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �X�e���V���V���h�E�e�X�gClass
//!
//! @details �X�e���V���V���h�E�e�X�g��Class
//************************************************************
class StencilShadowTest : public GameObjectNull
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw);
};



#endif