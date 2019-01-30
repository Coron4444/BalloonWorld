//================================================================================
//!	@file	 GoalFactory.h
//!	@brief	 ゴール生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================
#ifndef	_GOAL_FACTORY_H_
#define _GOAL_FACTORY_H_



//****************************************
// クラス宣言
//****************************************
class Goal;



//************************************************************														   
//! @brief   ゴール生成Class
//!
//! @details ゴールの生成Class
//************************************************************
class GoalFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief ゴール生成関数
	//! @details
	//! @param void なし
	//! @retval Goal* ゴール
	//----------------------------------------
	Goal* Create();
};



#endif