//================================================================================
//!	@file	 PlayerFactory.cpp
//!	@brief	 プレイヤー生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/23
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PlayerFactory.h"



//****************************************
// 関数定義
//****************************************
Player* PlayerFactory::Create()
{
	Player* temp = new Player();
	temp->Init(new PlayerUpdate(),
			   new PlayerDraw(),
			   new PlayerCollision());
	return temp;
}