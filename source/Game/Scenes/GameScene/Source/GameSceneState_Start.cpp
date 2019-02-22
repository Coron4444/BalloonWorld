//================================================================================
//!	@file	 GameSceneState_Start.cpp
//!	@brief	 �Q�[���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameSceneState_Start.h"
#include "../GameSceneState_Play.h"
#include "../GameScene.h"

#include <GameEngine/Draw/DrawManager/DrawManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <Tool/SafeRelease.h>

#include <Object/3D/StageManager/StageManager.h>

#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>



//****************************************
// �֐���`
//****************************************
void GameSceneState_Start::Init()
{
	// �X�e�[�gID�o�^
	setID((int)GameScene::State::START);
	
	// �Q�[���V�[���̎擾
	game_scene_ = (GameScene*)getpScene();

	// �X�e�[�W�X�VOFF
	game_scene_->getpStageManager()->setIsEnable(false);
}



void GameSceneState_Start::Update()
{
	// �t�F�[�h�C�����͔r��
	if (!game_scene_->getpSceneManager()->getpCommonData()->getIsUpdate()) return;

	// �X�^�[�g���S�A�j���[�V�����I����
	game_scene_->setState(new GameSceneState_Play());
}



void GameSceneState_Start::PauseEntrance()
{
	
}



void GameSceneState_Start::PauseExit()
{
	
}