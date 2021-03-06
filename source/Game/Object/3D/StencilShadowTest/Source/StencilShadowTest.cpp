//================================================================================
//!	@file	 StencilShadowTest.h
//!	@brief	 ステンシルシャドウテストClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StencilShadowTest.h"



//****************************************
// 関数定義
//****************************************
void StencilShadowTest::Init(DrawBase* draw)
{
	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}