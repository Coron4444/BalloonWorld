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

#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/SafeRelease.h>

#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>



//****************************************
// 関数定義
//****************************************
void GameSceneState_End::Init()
{
	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();
	setID((int)GameScene::State::END);
}



void GameSceneState_End::Update()
{
	// クリア
	//if (game_scene_->getGameOver() == 0)
	//{
	//	game_scene_->getpSceneManager()->getpCommonData()->setIsClear(true);
	//	game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
	//}
}