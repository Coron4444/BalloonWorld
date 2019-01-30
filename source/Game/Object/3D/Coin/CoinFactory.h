//================================================================================
//!	@file	 CoinFactory.h
//!	@brief	 �R�C������Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_FACTORY_H_
#define _COIN_FACTORY_H_



//****************************************
// �N���X�錾
//****************************************
class Coin;



//************************************************************														   
//! @brief   �R�C������Class
//!
//! @details �R�C���̐���Class
//************************************************************
class CoinFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R�C�������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Coin* �R�C��
	//----------------------------------------
	Coin* Create();
};



#endif