//================================================================================
//!	@file	 BalloonNumFactory.cpp
//!	@brief	 ���D������Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonNumFactory.h"



//****************************************
// �֐���`
//****************************************
BalloonNum* BalloonNumFactory::Create()
{
	BalloonNum* temp = new BalloonNum();
	temp->Init(new BalloonNumDraw());
	return temp;
}