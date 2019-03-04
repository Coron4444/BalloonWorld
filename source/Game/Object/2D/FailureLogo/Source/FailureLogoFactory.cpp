//================================================================================
//!	@file	 FailureLogoFactory.cpp
//!	@brief	 失敗ロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../FailureLogoFactory.h"



//****************************************
// 関数定義
//****************************************
FailureLogo* FailureLogoFactory::Create()
{
	FailureLogo* temp = new FailureLogo();
	temp->Init(new FailureLogoDraw());
	return temp;
}