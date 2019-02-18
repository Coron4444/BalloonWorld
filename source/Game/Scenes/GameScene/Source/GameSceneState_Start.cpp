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
#include "../GameScene.h"

#include <GameEngine/Draw/DrawManager/DrawManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/SafeRelease.h>

#include <Object/3D/StageManager/StageManager.h>
#include <Object/3D/Player/Player.h>
#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>



//****************************************
// 関数定義
//****************************************
void GameSceneState_Start::Init()
{
	// ゲームシーンの取得
	game_scene_ = (GameScene*)getpScene();

	// ゲームシーン共通データーの初期化
	//game_scene_->setIsClear(false);
	//game_scene_->setScore(0);

	// デフォルトカメラの作成
	Camera* camera = GameObjectManager::getpInstance()->getpDrawManager()
		->getpCamera(DrawManager::RenderTargetType::MAIN);
	//Camera::State* camera_state = new CameraState_CrawlUp();
	Camera::State* camera_state = new CameraState_HomingTarget();
	camera->setState(camera_state);
	
	// プレイヤーにカメラを設定
	game_scene_->getpStageManager()->setPlayerCamera(camera);
	((CameraState_HomingTarget*)camera_state)->setTargetObject(game_scene_->getpStageManager()
															   ->getpPlayer());
}



void GameSceneState_Start::Update()
{
	// クリア
	//if (game_scene_->getGameOver() == 0)
	//{
	//	game_scene_->getpSceneManager()->getpCommonData()->setIsClear(true);
	//	game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
	//}
	//
	//// 失敗
	//if (game_scene_->getGameOver() == 1)
	//{
	//	game_scene_->getpSceneManager()->getpCommonData()->setIsClear(false);
	//	game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
	//}
}