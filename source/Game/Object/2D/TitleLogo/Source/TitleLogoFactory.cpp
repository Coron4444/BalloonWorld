//================================================================================
//!	@file	 TitleLogoFactory.cpp
//!	@brief	 タイトルロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../TitleLogoFactory.h"
#include "../TitleLogo.h"
#include "../TitleLogoDraw.h"



//****************************************
// 関数定義
//****************************************
TitleLogo* TitleLogoFactory::Create()
{
	TitleLogo* temp = new TitleLogo();
	temp->Init(new TitleLogoDraw());
	return temp;
}