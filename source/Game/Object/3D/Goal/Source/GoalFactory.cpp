//================================================================================
//!	@file	 GoalFactory.cpp
//!	@brief	 �S�[������Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GoalFactory.h"
#include "../Goal.h"
#include "../GoalDraw.h"
#include "../GoalCollision.h"



//****************************************
// �֐���`
//****************************************
Goal* GoalFactory::Create()
{
	Goal* temp = new Goal();
	temp->Init(new GoalDraw(),
			   new GoalCollision());
	return temp;
}