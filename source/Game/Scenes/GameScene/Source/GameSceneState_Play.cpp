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

#include <GameEngine/Draw/DrawManager/DrawManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>



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
	if ()
	game_scene_->setState(new GameSceneState_End());
}