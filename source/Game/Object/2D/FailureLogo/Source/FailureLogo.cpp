//================================================================================
//!	@file	 FailureLogo.cpp
//!	@brief	 失敗ロゴClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../FailureLogo.h"



//****************************************
// 関数定義
//****************************************
void FailureLogo::Init(DrawBase* draw)
{
	// 基底クラスの初期化
	GameObjectBase::Init(nullptr, draw, nullptr);
}