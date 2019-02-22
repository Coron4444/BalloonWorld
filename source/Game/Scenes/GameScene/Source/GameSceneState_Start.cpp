//================================================================================
//!	@file	 GameSceneState_Start.cpp
//!	@brief	 ゲームシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// インクルード文
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
// 関数定義
//****************************************
void GameSceneState_Start::Init()
{
	// ステートID登録
	setID((int)GameScene::State::START);
	
	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();

	// ステージ更新OFF
	game_scene_->getpStageManager()->setIsEnable(false);
}



void GameSceneState_Start::Update()
{
	// フェードイン中は排除
	if (!game_scene_->getpSceneManager()->getpCommonData()->getIsUpdate()) return;

	// スタートロゴアニメーション終了時
	game_scene_->setState(new GameSceneState_Play());
}



void GameSceneState_Start::PauseEntrance()
{
	
}



void GameSceneState_Start::PauseExit()
{
	
}