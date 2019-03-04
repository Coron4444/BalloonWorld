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
void Coin::Init(DrawBase* draw, CollisionBase* collision)
{
	// �F������
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;

	// ���N���X�̏�����
	GameObjectBase::Init(draw, collision);
}



void Coin::Update()
{
	if (*getpColorChangeCounter() > 1)
	{
		*getpColor() = {1.0f, 0.0f, 0.0f, 1.0f};
		*getpIsColorChange() = true;
		(*getpColorChangeCounter())--;
	}
	else if (*getpColorChangeCounter() == 1)
	{
		*getpColor() = {1.0f, 0.0f, 0.0f, 1.0f};
		*getpIsColorChange() = true;
		(*getpColorChangeCounter())--;
	}
}



void Coin::Reset()
{
	// �F������
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
}