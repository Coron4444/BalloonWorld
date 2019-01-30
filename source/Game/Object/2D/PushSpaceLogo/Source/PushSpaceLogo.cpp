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
void PushSpaceLogo::Init(UpdateBase* update, DrawBase* draw)
{
	// 色初期化
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;

	// 基底クラスの初期化
	GameObjectBase::Init(update, draw, nullptr);
}



void PushSpaceLogo::Reset()
{
	// 色リセット
	color_ = {1.0f, 1.0f, 1.0f, 1.0f};
	is_color_change_ = false;
	
	GameObjectBase::Reset();
}