//================================================================================
//!	@file	 BalloonGroupFactory.cpp
//!	@brief	 ���D�Q����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonGroupFactory.h"



//****************************************
// �֐���`
//****************************************
BalloonGroup* BalloonGroupFactory::Create(unsigned balloon_num)
{
	BalloonGroup* temp = new BalloonGroup();
	temp->Init(balloon_num);
	return temp;
}