//================================================================================
//!	@file	 Player.h
//!	@brief	 �v���C���[����Class
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================
#ifndef	_PLAYER_H_
#define _PLAYER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   �v���C���[Class
//!
//! @details �v���C���[��Class
//************************************************************
class Player : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	GameScene* game_scene_ = nullptr;			//!< �Q�[���V�[��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Q�[���V�[���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval GameScene* �Q�[���V�[��
	//----------------------------------------
	GameScene* getpGameScene();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *update     �X�V���N���X
	//! @param *draw       �`����N���X
	//! @param *collision  �Փˊ��N���X
	//! @param *game_scene �Q�[���V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision, 
			  GameScene* game_scene);
};



#endif