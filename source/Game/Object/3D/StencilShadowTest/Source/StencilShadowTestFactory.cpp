//================================================================================
//!	@file	 StencilShadowTestFactory.cpp
//!	@brief	 ステンシルシャドウテスト生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StencilShadowTestFactory.h"



//****************************************
// 関数定義
//****************************************
StencilShadowTest* StencilShadowTestFactory::Create()
{
	StencilShadowTest* temp = new StencilShadowTest();
	temp->Init(new StencilShadowTestDraw());
	return temp;
}