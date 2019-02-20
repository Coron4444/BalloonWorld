//================================================================================
//!	@file	 ScaffoldFactory.cpp
//!	@brief	 ���ꐶ��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ScaffoldFactory.h"



//****************************************
// �֐���`
//****************************************
Scaffold* ScaffoldFactory::Create()
{
	Scaffold* temp = new Scaffold();
	temp->Init(new ScaffoldDraw(),
			   new ScaffoldCollision());
	return temp;
}