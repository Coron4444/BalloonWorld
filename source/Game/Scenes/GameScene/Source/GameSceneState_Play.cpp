//================================================================================
//!	@file	 GameSceneState_Play.cpp
//!	@brief	 ゲームシーンステート(プレイ)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameSceneState_Play.h"
#include "../GameSceneState_End.h"
#include "../GameScene.h"

#include <GameEngine/Draw/DrawManager/DrawManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>



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
	if ()
	game_scene_->setState(new GameSceneState_End());
}