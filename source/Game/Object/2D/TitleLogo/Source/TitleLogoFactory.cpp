//================================================================================
//!	@file	 TitleLogoFactory.cpp
//!	@brief	 �^�C�g�����S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TitleLogoFactory.h"
#include "../TitleLogo.h"
#include "../TitleLogoDraw.h"



//****************************************
// �֐���`
//****************************************
TitleLogo* TitleLogoFactory::Create()
{
	TitleLogo* temp = new TitleLogo();
	temp->Init(new TitleLogoDraw());
	return temp;
}