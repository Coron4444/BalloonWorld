//================================================================================
//!	@file	 GameSceneState_Play.cpp
//!	@brief	 �Q�[���V�[���X�e�[�g(�v���C)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameSceneState_Play.h"
#include "../GameSceneState_End.h"
#include "../GameScene.h"

#include <Object/3D/StageManager/StageManager.h>



//****************************************
// �֐���`
//****************************************
void GameSceneState_Play::Init()
{
	// �Q�[���V�[���̎擾
	game_scene_ = (GameScene*)getpScene();

	// �X�e�[�W�X�VON
	game_scene_->getpStageManager()->setIsEnable(true);
}



void GameSceneState_Play::Update()
{
	// UI�ݒ�
	game_scene_->setAllUI();

	// �v���C���[���n�ʂɒ�������
	if (game_scene_->getpStageManager()->getIsOnTheGround())
	{
		game_scene_->setState(new GameSceneState_End());
	}
}



void GameSceneState_Play::PauseEntrance()
{
	// �X�e�[�W�X�VOFF
	game_scene_->getpStageManager()->setIsEnable(false);
}



void GameSceneState_Play::PauseExit()
{
	// �X�e�[�W�X�VON
	game_scene_->getpStageManager()->setIsEnable(true);
}