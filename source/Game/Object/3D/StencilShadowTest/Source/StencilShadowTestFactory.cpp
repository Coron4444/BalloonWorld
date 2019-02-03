//================================================================================
//!	@file	 StencilShadowTestFactory.cpp
//!	@brief	 �X�e���V���V���h�E�e�X�g����Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StencilShadowTestFactory.h"



//****************************************
// �֐���`
//****************************************
StencilShadowTest* StencilShadowTestFactory::Create()
{
	StencilShadowTest* temp = new StencilShadowTest();
	temp->Init(new StencilShadowTestDraw());
	return temp;
}