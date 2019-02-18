//================================================================================
//!	@file	 GameSceneState_Pause.cpp
//!	@brief	 ゲームシーンステート(ポーズ)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameSceneState_Play.h"
#include "../GameSceneState_Start.h"
#include "../GameScene.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>

#include <Scenes/TitleScene/TitleSceneState_Start.h>



//****************************************
// 関数定義
//****************************************
void GameSceneState_Play::Init()
{
	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();
}



void GameSceneState_Play::Update()
{
	game_scene_->setState(new GameSceneState_End());
}