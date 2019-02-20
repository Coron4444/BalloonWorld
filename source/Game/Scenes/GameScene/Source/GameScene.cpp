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

#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/Input/InputManager/InputManager.h>

#include <Object/2D/Score/ScoreFactory.h>
#include <Object/2D/Pause/PauseFactory.h>
#include <Object/3D/Coin/CoinFactory.h>
#include <Object/3D/Enemy/EnemyFactory.h>
#include <Object/3D/Field/FieldFactory.h>
#include <Object/3D/Goal/GoalFactory.h>
#include <Object/3D/SkyDome/SkyDomeFactory.h>
#include <Object/3D/StageManager/StageManager.h>

#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState_Start.h>



//****************************************
// プロパティ定義
//****************************************
int GameScene::getTime()
{ 
	return time_;
}



void GameScene::setTime(int value)
{ 
	time_ = value;
}



StageManager* GameScene::getpStageManager()
{
	return stage_manager_;
}



void GameScene::setStageManager(StageManager* value)
{
	stage_manager_ = value;
}



Pause* GameScene::getpPause()
{
	return pause_;
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
	// ポーズ作成
	PauseFactory pause_factory_;
	pause_ = pause_factory_.Create();
	pause_->setIsEnable(false);

	// コインの作成
	CoinFactory coin_factory;
	Coin* temp = coin_factory.Create();
	*temp->getpTransform()->getpPosition() = Vec3(5.0f, 1.0f, 0.0f);
	temp->getpTransform()->CreateWorldMatrix();
	
	temp = coin_factory.Create();
	*temp->getpTransform()->getpPosition() = Vec3(5.0f, 1.0f, 5.0f);
	temp->getpTransform()->CreateWorldMatrix();
	
	temp = coin_factory.Create();
	*temp->getpTransform()->getpPosition() = Vec3(-5.0f, 1.0f, -5.0f);
	temp->getpTransform()->CreateWorldMatrix();

	// スカイドーム
	SkyDomeFactory sky_dome_factory;
	sky_dome_factory.Create();

	// フィールド
	FieldFactory field_factory;
	Field* field = field_factory.Create();
	GameObjectManager::getpInstance()->getpCollisionManager()
		->setGround(field->getpMeshPlanePolygon());

	// ステージ
	stage_manager_ = new StageManager();
	stage_manager_->Init();
	stage_manager_->CreateStage();
	
	// 敵
	EnemyFactory enemy_factory;
	Enemy* temp2 = enemy_factory.Create();
	*temp2->getpTransform()->getpPosition() = Vec3(-5.0f, 6.0f, 5.0f);
	*temp2->getpTransform()->getpScale() = Vec3(3.0f, 3.0f, 3.0f);
	//*temp2->getpTransform()->getpAngleYaw() += 3.0f;
	temp2->getpTransform()->CreateWorldMatrix();

	// ゴール
	GoalFactory goal_factory;
	Goal* temp3 = goal_factory.Create();
	*temp3->getpTransform()->getpPosition() = Vec3(10.0f, 0.0f, 20.0f);
	temp3->getpTransform()->CreateWorldMatrix();

	// スコア
	//ScoreFactory score_factory;
	//score_factory.Create(this);

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
				getpSceneManager()->setResetScene(new GameSceneState_Start());
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
			}
			else
			{
				setIsPause(true);
				pause_->setIsEnable(true);
			}
		}
	}
}