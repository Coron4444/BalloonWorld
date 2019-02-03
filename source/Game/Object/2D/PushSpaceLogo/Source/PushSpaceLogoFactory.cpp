//================================================================================
//!	@file	 PushSpaceLogoFactory.cpp
//!	@brief	 �v�b�V���X�y�[�X���S����Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PushSpaceLogoFactory.h"



//****************************************
// �֐���`
//****************************************
PushSpaceLogo* PushSpaceLogoFactory::Create()
{
	PushSpaceLogo* temp = new PushSpaceLogo();
	temp->Init(new PushSpaceLogoUpdate(),
			   new PushSpaceLogoDraw());
	return temp;
}