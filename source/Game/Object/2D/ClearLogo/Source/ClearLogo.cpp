//================================================================================
//!	@file	 ClearLogo.cpp
//!	@brief	 クリアロゴClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ClearLogo.h"

int ClearLogo::getScore()
{
	return score_;
}

void ClearLogo::setScore(int value)
{
	score_ = value;
}

//****************************************
// 関数定義
//****************************************
void ClearLogo::Init(DrawBase* draw)
{
	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}