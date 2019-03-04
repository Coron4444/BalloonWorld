//================================================================================
//!	@file	 TutorialLogo.cpp
//!	@brief	 �`���[�g���A�����SClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TutorialLogo.h"



//****************************************
// �v���p�e�B��`
//****************************************
unsigned TutorialLogo::getLogoNum()
{
	return logo_num_;
}



void TutorialLogo::setLogoNum(unsigned value)
{
	logo_num_ = value;
}



//****************************************
// �֐���`
//****************************************
void TutorialLogo::Init(DrawBase* draw)
{
	logo_num_ = 0;

	// ���N���X�̏�����
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}



void TutorialLogo::Reset()
{
	logo_num_ = 0;
}