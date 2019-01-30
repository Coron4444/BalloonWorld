//================================================================================
//!	@file	 CoinUpdate.cpp
//!	@brief	 �v�b�V���X�y�[�X���S�X�VClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CoinUpdate.h"
#include "../Coin.h"



//****************************************
// �֐���`
//****************************************
void CoinUpdate::Init()
{
	// �_�E���L���X�g
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