//================================================================================
//!	@file	 ClearLogoFactory.cpp
//!	@brief	 �N���A���S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ClearLogoFactory.h"
#include "../ClearLogo.h"
#include "../ClearLogoDraw.h"



//****************************************
// �֐���`
//****************************************
ClearLogo* ClearLogoFactory::Create()
{
	ClearLogo* temp = new ClearLogo();
	temp->Init(new ClearLogoDraw());
	return temp;
}