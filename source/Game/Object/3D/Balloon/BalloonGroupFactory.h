//================================================================================
//!	@file	 BalloonGroupFactory.h
//!	@brief	 ���D�Q����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_BALLOON_GROUP_FACTORY_H_
#define _BALLOON_GROUP_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "BalloonGroup.h"



//************************************************************														   
//! @brief   ���D�Q����Class
//!
//! @details ���D�Q�̐���Class
//************************************************************
class BalloonGroupFactory
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���D�Q�����֐�
	//! @details
	//! @param balloon_num ���D��
	//! @retval BalloonGroup* ���D�Q
	//----------------------------------------
	BalloonGroup* Create(unsigned balloon_num);
};



#endif