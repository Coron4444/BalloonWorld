//================================================================================
//!	@file	 StartBlockFactory.cpp
//!	@brief	 スタートブロック生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StartBlockFactory.h"



//****************************************
// 関数定義
//****************************************
StartBlock* StartBlockFactory::Create()
{
	StartBlock* temp = new StartBlock();
	temp->Init(new StartBlockDraw(),
			   new StartBlockCollision());
	return temp;
}