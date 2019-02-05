//================================================================================
//!	@file	 Player.cpp
//!	@brief	 �v���C���[Class
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Player.h"



//****************************************
// �v���p�e�B��`
//****************************************
GameScene* Player::getpGameScene()
{
	return game_scene_;
}



//****************************************
// �֐���`
//****************************************
void Player::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision,
				  GameScene* game_scene)
{
	// �e����
	game_scene_ = game_scene;

	// ���N���X�̏�����
	GameObjectBase::Init(update, draw, collision);
}