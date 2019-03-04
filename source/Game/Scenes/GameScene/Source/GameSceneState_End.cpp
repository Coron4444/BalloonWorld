//================================================================================
//!	@file	 GameSceneState_End.cpp
//!	@brief	 �Q�[���V�[���X�e�[�g(�ŏI)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameSceneState_End.h"
#include "../GameScene.h"

#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>

#include <Object/3D/StageManager/StageManager.h>



//****************************************
// �֐���`
//****************************************
void GameSceneState_End::Init()
{
	setID((int)GameScene::State::END);

	// �Q�[���V�[���̎擾
	game_scene_ = (GameScene*)getpScene();
}



void GameSceneState_End::Update()
{
	// �N���A
	game_scene_->getpSceneManager()->getpCommonData()->setScore(game_scene_->getpStageManager()->getScore());
	game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
}