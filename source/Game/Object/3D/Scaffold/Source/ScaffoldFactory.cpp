//================================================================================
//!	@file	 ScaffoldFactory.cpp
//!	@brief	 足場生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ScaffoldFactory.h"



//****************************************
// 関数定義
//****************************************
Scaffold* ScaffoldFactory::Create()
{
	Scaffold* temp = new Scaffold();
	temp->Init(new ScaffoldDraw(),
			   new ScaffoldCollision());
	return temp;
}