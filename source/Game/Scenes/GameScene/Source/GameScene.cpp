//================================================================================
//!	@file	 GameScene.cpp
//!	@brief	 ゲームシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameScene.h"
#include "../GameSceneState_Start.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>

#include <Object/2D/Score/ScoreFactory.h>
#include <Object/2D/Pause/PauseFactory.h>
#include <Object/2D/Time/TimeFactory.h>
#include <Object/2D/BalloonNum/BalloonNumFactory.h>
#include <Object/3D/StageManager/StageManager.h>
#include <Object/3D/Player/Player.h>

#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState_Start.h>



//****************************************
// プロパティ定義
//****************************************
StageManager* GameScene::getpStageManager()
{
	return stage_manager_;
}



void GameScene::setStageManager(StageManager* value)
{
	stage_manager_ = value;
}



Score* GameScene::getpScore()
{
	return score_;
}



Time* GameScene::getpTime()
{
	return time_;
}



BalloonNum* GameScene::getpBalloonNum()
{
	return balloon_num_;
}



void GameScene::setAllUI()
{
	score_->setScore(stage_manager_->getScore());
	time_->setTime(stage_manager_->getTime());
	balloon_num_->setBalloonNum(stage_manager_->getBalloonNum());
}



//****************************************
// 関数定義
//****************************************
GameScene::GameScene(StateBase* state)
	: SceneNull(state) 
{
}



void GameScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_STAGE);

	// ポーズ作成
	PauseFactory pause_factory_;
	pause_ = pause_factory_.Create();
	pause_->setIsEnable(false);

	// ステージ
	stage_manager_ = new StageManager();
	stage_manager_->Init();
	stage_manager_->CreateStage();

	// スコア
	ScoreFactory score_factory;
	score_ = score_factory.Create();
	
	// 時間
	TimeFactory time_factory;
	time_ = time_factory.Create();
	
	// 風船数
	BalloonNumFactory balloon_num_factory;
	balloon_num_ = balloon_num_factory.Create();
	

	// カメラステート変更
	Camera* camera = GameObjectManager::getpInstance()->getpDrawManager()
		->getpCamera(DrawManager::RenderTargetType::MAIN);
	Camera::State* camera_state = new CameraState_HomingTarget();
	camera->setState(camera_state);

	// プレイヤーにカメラセット
	stage_manager_->setPlayerCamera(camera);
	((CameraState_HomingTarget*)camera_state)->setTargetObject(stage_manager_->getpPlayer());

	// UI設定
	setAllUI();

	// ステート初期化
	SceneNull::Init();
}



void GameScene::Update()
{
	UpdateState();

	// ポーズ
	if (getCurrentStateID() == (int)State::END) return;
	if (pause_->getIsDecision())
	{
		switch (pause_->getSelectType())
		{
			case Pause::SelectType::CONTINUE:
			{
				setIsPause(false);
				pause_->setIsEnable(false);
				break;
			}
			case Pause::SelectType::RESTART:
			{
				getpSceneManager()->setNextScene(new GameScene(new GameSceneState_Start()));
				pause_->setIsEnable(false);
				break;
			}
			case Pause::SelectType::QUIT:
			{
				getpSceneManager()->setNextScene(new TitleScene(new TitleSceneState_Start()));
				pause_->setIsEnable(false);
				break;
			}
		}
	}
	else
	{
		if (!pause_->getIsInput()) return;
		if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_P) ||
			InputManager::getpInstance()->getpController()
			->getRelease(0, XINPUT_GAMEPAD_START))
		{
			if (getIsPause())
			{
				setIsPause(false);
				pause_->setIsEnable(false);
				SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_OPEN);
			}
			else
			{
				setIsPause(true);
				pause_->setIsEnable(true);
				SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_CLOSE);
			}
		}
	}
}



void GameScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_STAGE);

	// ステート終了
	SceneNull::Uninit();
}