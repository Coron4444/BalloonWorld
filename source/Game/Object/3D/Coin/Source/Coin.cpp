//================================================================================
//!	@file	 Coin.cpp
//!	@brief	 �R�C��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Coin.h"



//****************************************
// �v���p�e�B��`
//****************************************
int* Coin::getpColorChangeCounter()
{
	return &color_change_counter_;
}


	
XColor4* Coin::getpColor()
{
	return &color_;
}



bool* Coin::getpIsColorChange()
{
	return &is_color_change_;
}



//****************************************
// �֐���`
//****************************************
void Coin::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision)
{
	// �F������
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;

	// ���N���X�̏�����
	GameObjectBase::Init(update, draw, collision);
}



void Coin::Reset()
{
	// �F������
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
}