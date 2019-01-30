//================================================================================
//!	@file	 GoalFactory.cpp
//!	@brief	 ゴール生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GoalFactory.h"
#include "../Goal.h"
#include "../GoalDraw.h"
#include "../GoalCollision.h"



//****************************************
// 関数定義
//****************************************
Goal* GoalFactory::Create()
{
	Goal* temp = new Goal();
	temp->Init(new GoalDraw(),
			   new GoalCollision());
	return temp;
}