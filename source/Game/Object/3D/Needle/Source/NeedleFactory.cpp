//================================================================================
//!	@file	 NeedleFactory.cpp
//!	@brief	 棘生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../NeedleFactory.h"



//****************************************
// 関数定義
//****************************************
Needle* NeedleFactory::Create(Needle::State* state)
{
	Needle* temp = new Needle();
	temp->Init(new NeedleDraw(), new NeedleCollision());
	temp->setState(state);
	return temp;
}