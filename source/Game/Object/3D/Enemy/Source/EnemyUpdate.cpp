//================================================================================
//!	@file	 EnemyUpdate.cpp
//!	@brief	 �G�X�VClass
//! @details 
//!	@author  Kai Araki									@date 2019/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../EnemyUpdate.h"
#include "../Enemy.h"



//****************************************
// �萔��`
//****************************************
const float EnemyUpdate::SPEED = 0.1f;



//****************************************
// �֐���`
//****************************************
void EnemyUpdate::Init()
{
	// �_�E���L���X�g
	enemy_ = (Enemy*)getpGameObject();
}



void EnemyUpdate::Update()
{
}