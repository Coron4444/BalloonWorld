//================================================================================
//!	@file	 PushSpaceLogoFactory.h
//!	@brief	 プッシュスペースロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_PUSH_SPACE_LOGO_FACTORY_H_
#define _PUSH_SPACE_LOGO_FACTORY_H_



//****************************************
// インクルード文
//****************************************
#include "PushSpaceLogo.h"
#include "PushSpaceLogoUpdate.h"
#include "PushSpaceLogoDraw.h"



//************************************************************														   
//! @brief   プッシュスペースロゴ生成Class
//!
//! @details プッシュスペースロゴの生成Class
//************************************************************
class PushSpaceLogoFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief プッシュスペースロゴ生成関数
	//! @details
	//! @param void なし
	//! @retval PushSpaceLogo* プッシュスペースロゴ
	//----------------------------------------
	PushSpaceLogo* Create();
};



#endif