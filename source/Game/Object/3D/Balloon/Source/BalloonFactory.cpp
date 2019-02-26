//================================================================================
//!	@file	 BalloonFactory.cpp
//!	@brief	 風船生成Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonFactory.h"



//****************************************
// 関数定義
//****************************************
Balloon* BalloonFactory::Create(unsigned balloon_line_num, Vector3D position)
{
	Balloon* temp = new Balloon();
	temp->Init(new BalloonDraw(), balloon_line_num, position);
	return temp;
}