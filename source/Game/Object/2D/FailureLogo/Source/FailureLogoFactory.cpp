//================================================================================
//!	@file	 FailureLogoFactory.cpp
//!	@brief	 ���s���S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../FailureLogoFactory.h"



//****************************************
// �֐���`
//****************************************
FailureLogo* FailureLogoFactory::Create()
{
	FailureLogo* temp = new FailureLogo();
	temp->Init(new FailureLogoDraw());
	return temp;
}