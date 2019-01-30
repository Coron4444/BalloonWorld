//================================================================================
//!	@file	 PushSpaceLogo.cpp
//!	@brief	 �v�b�V���X�y�[�X���SClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PushSpaceLogo.h"



//****************************************
// �v���p�e�B��`
//****************************************
XColor4* PushSpaceLogo::getpColor()
{
	return &color_;
}



bool* PushSpaceLogo::getpIsColorChange()
{
	return &is_color_change_;
}



//****************************************
// �֐���`
//****************************************
void PushSpaceLogo::Init(UpdateBase* update, DrawBase* draw)
{
	// �F������
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;

	// ���N���X�̏�����
	GameObjectBase::Init(update, draw, nullptr);
}



void PushSpaceLogo::Reset()
{
	// �F���Z�b�g
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	
	GameObjectBase::Reset();
}