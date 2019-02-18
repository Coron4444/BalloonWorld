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
	UninitComponent();
}



void GameObjectNull::Update()
{
}



void GameObjectNull::LateUpdate()
{
}



void GameObjectNull::Reset()
{
	ResetComponent();
}



void GameObjectNull::DebugDisplay()
{
}