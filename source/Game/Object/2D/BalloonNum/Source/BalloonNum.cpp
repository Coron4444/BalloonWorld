//================================================================================
//!	@file	 BalloonNum.cpp
//!	@brief	 風船数Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonNum.h"



//****************************************
// プロパティ定義
//****************************************
int BalloonNum::getBalloonNum()
{
	return balloon_num_;
}



void BalloonNum::setBalloonNum(int value)
{
	balloon_num_ = value;
}



//****************************************
// 関数定義
//****************************************
void BalloonNum::Init(DrawBase* draw)
{
	balloon_num_ = 0;

	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}