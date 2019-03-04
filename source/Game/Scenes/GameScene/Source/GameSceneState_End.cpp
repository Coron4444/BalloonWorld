//================================================================================
//!	@file	 GameSceneState_End.cpp
//!	@brief	 ゲームシーンステート(最終)Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameSceneState_End.h"
#include "../GameScene.h"

#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>

#include <Object/3D/StageManager/StageManager.h>



//****************************************
// 関数定義
//****************************************
void GameSceneState_End::Init()
{
	setID((int)GameScene::State::END);

	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();
}



void GameSceneState_End::Update()
{
	// クリア
	game_scene_->getpSceneManager()->getpCommonData()->setScore(game_scene_->getpStageManager()->getScore());
	game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
}