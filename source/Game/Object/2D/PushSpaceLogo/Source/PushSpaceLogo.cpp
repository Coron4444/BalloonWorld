//================================================================================
//!	@file	 PushSpaceLogo.cpp
//!	@brief	 プッシュスペースロゴClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PushSpaceLogo.h"



//****************************************
// 定数定義
//****************************************
const int PushSpaceLogo::COLOR_CHANGE_SPEED = TimeToFrame::SecondToFrame(1.0f);



//****************************************
// プロパティ定義
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
// 関数定義
//****************************************
void PushSpaceLogo::Init(DrawBase* draw)
{
	// 色初期化
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	color_change_counter_ = 0;

	// 基底クラスの初期化
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
	// 色リセット
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	color_change_counter_ = 0;
	
	ResetComponent();
}