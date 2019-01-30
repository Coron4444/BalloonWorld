//================================================================================
//!	@file	 CoinFactory.cpp
//!	@brief	 �R�C������Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CoinFactory.h"
#include "../Coin.h"
#include "../CoinUpdate.h"
#include "../CoinDraw.h"
#include "../CoinCollision.h"



//****************************************
// �֐���`
//****************************************
Coin* CoinFactory::Create()
{
	Coin* temp = new Coin();
	temp->Init(new CoinUpdate(), 
			   new CoinDraw(),
			   new CoinCollision());
	return temp;
}