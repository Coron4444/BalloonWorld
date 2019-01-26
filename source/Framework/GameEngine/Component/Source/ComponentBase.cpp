//================================================================================
//!	@file	 ComponentBase.cpp
//!	@brief	 �R���|�[�l���gBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "ComponentBase.h"



//****************************************
// �v���p�e�B��`
//****************************************
GameObjectBase* ComponentBase::getpGameObject()
{
	return game_object_; 
}



void ComponentBase::setGameObject(GameObjectBase* value)
{
	game_object_ = value; 
}



//****************************************
// �֐���`
//****************************************
ComponentBase::~ComponentBase()
{
}