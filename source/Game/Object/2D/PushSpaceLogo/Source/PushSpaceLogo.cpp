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
// �萔��`
//****************************************
const int PushSpaceLogo::COLOR_CHANGE_SPEED = TimeToFrame::SecondToFrame(1.0f);



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
void PushSpaceLogo::Init(DrawBase* draw)
{
	// �F������
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	color_change_counter_ = 0;

	// ���N���X�̏�����
	GameObjectBase::Init(draw, nullptr);
}



void PushSpaceLogo::Update()
{
	color_change_counter_++;

	if (color_change_counter_ >= COLOR_CHANGE_SPEED)
	{
		is_color_change_ = true;
		color_.a = color_.a == 1.0f	? 0.0f : 1.0f;
		color_change_counter_ = 0;
	}
}



void PushSpaceLogo::Reset()
{
	// �F���Z�b�g
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	color_change_counter_ = 0;
	
	ResetComponent();
}