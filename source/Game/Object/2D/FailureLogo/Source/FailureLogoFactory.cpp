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
#include "../FailureLogo.h"
#include "../FailureLogoDraw.h"



//****************************************
// �֐���`
//****************************************
FailureLogo* FailureLogoFactory::Create()
{
	FailureLogo* temp = new FailureLogo();
	temp->Init(new FailureLogoDraw());
	return temp;
}