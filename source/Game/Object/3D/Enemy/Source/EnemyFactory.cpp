//================================================================================
//!	@file	 EnemyFactory.cpp
//!	@brief	 敵生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../EnemyFactory.h"
#include "../Enemy.h"
#include "../EnemyUpdate.h"
#include "../EnemyDraw.h"
#include "../EnemyCollision.h"



//****************************************
// 関数定義
//****************************************
Enemy* EnemyFactory::Create()
{
	Enemy* temp = new Enemy();
	temp->Init(new EnemyUpdate(),
			   new EnemyDraw(),
			   new EnemyCollision());
	return temp;
}