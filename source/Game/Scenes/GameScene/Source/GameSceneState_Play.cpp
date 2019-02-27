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

#include <Object/3D/StageManager/StageManager.h>



//****************************************
// 関数定義
//****************************************
void GameSceneState_Play::Init()
{
	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();

	// ステージ更新ON
	game_scene_->getpStageManager()->setIsEnable(true);
}



void GameSceneState_Play::Update()
{
	// UI設定
	game_scene_->setAllUI();

	// プレイヤーが地面に着いたら
	if (game_scene_->getpStageManager()->getIsOnTheGround())
	{
		game_scene_->setState(new GameSceneState_End());
	}
}



void GameSceneState_Play::PauseEntrance()
{
	// ステージ更新OFF
	game_scene_->getpStageManager()->setIsEnable(false);
}



void GameSceneState_Play::PauseExit()
{
	// ステージ更新ON
	game_scene_->getpStageManager()->setIsEnable(true);
}