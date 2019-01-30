//================================================================================
//!	@file	 GameObjectNull.cpp
//!	@brief	 ゲームオブジェクト空白Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/30
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameObjectNull.h"



//****************************************
// 関数定義
//****************************************
GameObjectNull::GameObjectNull(bool is_registration)
	: GameObjectBase(is_registration)
{
}



GameObjectNull::~GameObjectNull()
{
}



void GameObjectNull::Uninit()
{
	// 基底クラスの終了処理
	GameObjectBase::Uninit();
}

void GameObjectNull::Reset()
{
	// 基底クラスのリセット処理
	GameObjectBase::Reset();
}