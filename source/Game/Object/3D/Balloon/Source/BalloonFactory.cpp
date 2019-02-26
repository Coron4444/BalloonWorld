//================================================================================
//!	@file	 BalloonFactory.cpp
//!	@brief	 ���D����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonFactory.h"



//****************************************
// �֐���`
//****************************************
Balloon* BalloonFactory::Create(unsigned balloon_line_num, Vector3D position)
{
	Balloon* temp = new Balloon();
	temp->Init(new BalloonDraw(), balloon_line_num, position);
	return temp;
}