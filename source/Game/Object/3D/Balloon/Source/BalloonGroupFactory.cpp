//================================================================================
//!	@file	 BalloonGroupFactory.cpp
//!	@brief	 風船群生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonGroupFactory.h"



//****************************************
// 関数定義
//****************************************
BalloonGroup* BalloonGroupFactory::Create(unsigned balloon_num)
{
	BalloonGroup* temp = new BalloonGroup();
	temp->Init(balloon_num);
	return temp;
}