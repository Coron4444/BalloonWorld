//================================================================================
//!	@file	 PushSpaceLogoUpdate.cpp
//!	@brief	 プッシュスペースロゴ更新Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PushSpaceLogoUpdate.h"
#include "../PushSpaceLogo.h"

#include <Tool/TimeToFrame.h>



//****************************************
// 定数定義
//****************************************
const int PushSpaceLogoUpdate::COLOR_CHANGE_SPEED = TimeToFrame::SecondToFrame(1.0f);



//****************************************
// 関数定義
//****************************************
void PushSpaceLogoUpdate::Init()
{
	// ダウンキャスト
	push_space_logo_ = (PushSpaceLogo*)getpGameObject();

	color_change_counter_ = 0;
}



void PushSpaceLogoUpdate::Update()
{
	color_change_counter_++;

	if (color_change_counter_ >= COLOR_CHANGE_SPEED)
	{
		*push_space_logo_->getpIsColorChange() = true;
		push_space_logo_->getpColor()->a = push_space_logo_->getpColor()->a == 1.0f 
			? 0.0f : 1.0f;

		color_change_counter_ = 0;
	}
}



void PushSpaceLogoUpdate::Reset()
{
	color_change_counter_ = 0;
}