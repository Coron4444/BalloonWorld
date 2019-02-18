//================================================================================
//!	@file	 GameSceneState_Pause.cpp
//!	@brief	 �Q�[���V�[���X�e�[�g(�|�[�Y)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameSceneState_Play.h"
#include "../GameSceneState_Start.h"
#include "../GameScene.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>

#include <Scenes/TitleScene/TitleSceneState_Start.h>



//****************************************
// �֐���`
//****************************************
void GameSceneState_Play::Init()
{
	// �Q�[���V�[���̎擾
	game_scene_ = (GameScene*)getpScene();
}



void GameSceneState_Play::Update()
{
	game_scene_->setState(new GameSceneState_End());
}