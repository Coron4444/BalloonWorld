//================================================================================
//!	@file	 TutorialLogo.cpp
//!	@brief	 チュートリアルロゴClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../TutorialLogo.h"



//****************************************
// プロパティ定義
//****************************************
unsigned TutorialLogo::getLogoNum()
{
	return logo_num_;
}



void TutorialLogo::setLogoNum(unsigned value)
{
	logo_num_ = value;
}



//****************************************
// 関数定義
//****************************************
void TutorialLogo::Init(DrawBase* draw)
{
	logo_num_ = 0;

	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}



void TutorialLogo::Reset()
{
	logo_num_ = 0;
}