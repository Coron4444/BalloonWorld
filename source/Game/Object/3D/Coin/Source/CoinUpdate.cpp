//================================================================================
//!	@file	 CoinUpdate.cpp
//!	@brief	 プッシュスペースロゴ更新Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CoinUpdate.h"
#include "../Coin.h"



//****************************************
// 関数定義
//****************************************
void CoinUpdate::Init()
{
	// ダウンキャスト
	coin_ = (Coin*)getpGameObject();
}



void CoinUpdate::Update()
{
	if (*coin_->getpColorChangeCounter() > 1)
	{
		*coin_->getpColor() = {1.0f, 0.0f, 0.0f, 1.0f};
		*coin_->getpIsColorChange() = true;
		(*coin_->getpColorChangeCounter())--;
	}
	else if (*coin_->getpColorChangeCounter() == 1)
	{
		*coin_->getpColor() = {1.0f, 0.0f, 0.0f, 1.0f};
		*coin_->getpIsColorChange() = true;
		(*coin_->getpColorChangeCounter())--;
	}
}