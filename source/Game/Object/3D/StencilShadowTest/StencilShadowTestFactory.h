//================================================================================
//!	@file	 StencilShadowTestFactory.h
//!	@brief	 ステンシルシャドウテスト生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_STENCIL_SHADOW_TEST_FACTORY_H_
#define _STENCIL_SHADOW_TEST_FACTORY_H_



//****************************************
// インクルード文
//****************************************
#include "StencilShadowTest.h"
#include "StencilShadowTestDraw.h"



//************************************************************														   
//! @brief   ステンシルシャドウテスト生成Class
//!
//! @details ステンシルシャドウテストの生成Class
//************************************************************
class StencilShadowTestFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief ステンシルシャドウテスト生成関数
	//! @details
	//! @param void なし
	//! @retval StencilShadowTest* ステンシルシャドウテスト
	//----------------------------------------
	StencilShadowTest* Create();
};



#endif