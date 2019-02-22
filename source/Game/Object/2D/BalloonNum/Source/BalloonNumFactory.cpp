//================================================================================
//!	@file	 BalloonNumFactory.cpp
//!	@brief	 風船数生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonNumFactory.h"



//****************************************
// 関数定義
//****************************************
BalloonNum* BalloonNumFactory::Create()
{
	BalloonNum* temp = new BalloonNum();
	temp->Init(new BalloonNumDraw());
	return temp;
}