//================================================================================
//!	@file	 GameObjectNull.cpp
//!	@brief	 �Q�[���I�u�W�F�N�g��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/30
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameObjectNull.h"



//****************************************
// �֐���`
//****************************************
GameObjectNull::GameObjectNull(bool is_registration)
	: GameObjectBase(is_registration)
{
}



GameObjectNull::~GameObjectNull()
{
}



void GameObjectNull::Uninit()
{
	UninitComponent();
}



void GameObjectNull::Update()
{
}



void GameObjectNull::LateUpdate()
{
}



void GameObjectNull::Reset()
{
	ResetComponent();
}



void GameObjectNull::DebugDisplay()
{
}