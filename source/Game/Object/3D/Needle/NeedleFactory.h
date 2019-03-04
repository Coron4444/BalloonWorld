//================================================================================
//!	@file	 NeedleFactory.h
//!	@brief	 棘生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_NEEDLE_FACTORY_H_
#define _NEEDLE_FACTORY_H_



//****************************************
// インクルード文
//****************************************
#include "Needle.h"
#include "NeedleDraw.h"
#include "NeedleCollision.h"
#include "NeedleState_Loop.h"



//************************************************************														   
//! @brief   棘生成Class
//!
//! @details 棘の生成Class
//************************************************************
class NeedleFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 棘生成関数
	//! @details
	//! @param *state ステート
	//! @retval Needle* 棘
	//----------------------------------------
	Needle* Create(Needle::State* state);
};



#endif