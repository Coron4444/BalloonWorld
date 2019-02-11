//================================================================================
//!	@file	 BalloonGroupFactory.h
//!	@brief	 風船群生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_BALLOON_GROUP_FACTORY_H_
#define _BALLOON_GROUP_FACTORY_H_



//****************************************
// インクルード文
//****************************************
#include "BalloonGroup.h"



//************************************************************														   
//! @brief   風船群生成Class
//!
//! @details 風船群の生成Class
//************************************************************
class BalloonGroupFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 風船群生成関数
	//! @details
	//! @param balloon_num 風船数
	//! @retval BalloonGroup* 風船群
	//----------------------------------------
	BalloonGroup* Create(unsigned balloon_num);
};



#endif