//================================================================================
//!	@file	 PlayerFactory.cpp
//!	@brief	 �v���C���[����Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/23
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PlayerFactory.h"



//****************************************
// �֐���`
//****************************************
Player* PlayerFactory::Create(GameScene* game_scene)
{
	Player* temp = new Player();
	temp->Init(new PlayerUpdate(),
			   new PlayerDraw(),
			   new PlayerCollision(),
			   game_scene);
	return temp;
}