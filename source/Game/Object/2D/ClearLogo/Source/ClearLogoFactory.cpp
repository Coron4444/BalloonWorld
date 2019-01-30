//================================================================================
//!	@file	 ClearLogoFactory.cpp
//!	@brief	 クリアロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ClearLogoFactory.h"
#include "../ClearLogo.h"
#include "../ClearLogoDraw.h"



//****************************************
// 関数定義
//****************************************
ClearLogo* ClearLogoFactory::Create()
{
	ClearLogo* temp = new ClearLogo();
	temp->Init(new ClearLogoDraw());
	return temp;
}