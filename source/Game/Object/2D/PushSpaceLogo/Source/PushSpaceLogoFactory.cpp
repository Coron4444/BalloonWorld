//================================================================================
//!	@file	 PushSpaceLogoFactory.cpp
//!	@brief	 プッシュスペースロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PushSpaceLogoFactory.h"



//****************************************
// 関数定義
//****************************************
PushSpaceLogo* PushSpaceLogoFactory::Create()
{
	PushSpaceLogo* temp = new PushSpaceLogo();
	temp->Init(new PushSpaceLogoUpdate(),
			   new PushSpaceLogoDraw());
	return temp;
}