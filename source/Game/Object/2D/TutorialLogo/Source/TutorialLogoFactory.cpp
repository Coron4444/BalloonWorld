//================================================================================
//!	@file	 TutorialLogoFactory.cpp
//!	@brief	 �`���[�g���A�����S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TutorialLogoFactory.h"



//****************************************
// �֐���`
//****************************************
TutorialLogo* TutorialLogoFactory::Create()
{
	TutorialLogo* temp = new TutorialLogo();
	temp->Init(new TutorialLogoDraw());
	return temp;
}