//================================================================================
//!	@file	 ClearLogoFactory.h
//!	@brief	 クリアロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_CLEAR_LOGO_FACTORY_H_
#define _CLEAR_LOGO_FACTORY_H_



//****************************************
// クラス宣言
//****************************************
class ClearLogo;



//************************************************************														   
//! @brief   クリアロゴ生成Class
//!
//! @details クリアロゴの生成Class
//************************************************************
class ClearLogoFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief クリアロゴ生成関数
	//! @details
	//! @param void なし
	//! @retval ClearLogo* クリアロゴ
	//----------------------------------------
	ClearLogo* Create();
};



#endif