//================================================================================
//!	@file	 NeedleFactory.cpp
//!	@brief	 ������Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../NeedleFactory.h"



//****************************************
// �֐���`
//****************************************
Needle* NeedleFactory::Create(Needle::State* state)
{
	Needle* temp = new Needle();
	temp->Init(new NeedleDraw(), new NeedleCollision());
	temp->setState(state);
	return temp;
}