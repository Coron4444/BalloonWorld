//================================================================================
//!	@file	 Coin.cpp
//!	@brief	 コインClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Coin.h"



//****************************************
// プロパティ定義
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
// 関数定義
//****************************************
void Coin::Init(DrawBase* draw, CollisionBase* collision)
{
	// 色初期化
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;

	// 基底クラスの初期化
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
	// 色初期化
	color_change_counter_ = 0;
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
}