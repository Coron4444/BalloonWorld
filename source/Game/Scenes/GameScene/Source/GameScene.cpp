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

#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>

#include <Object/2D/Score/ScoreFactory.h>
#include <Object/3D/Coin/CoinFactory.h>
#include <Object/3D/Enemy/EnemyFactory.h>
#include <Object/3D/Field/FieldFactory.h>
#include <Object/3D/Goal/GoalFactory.h>
#include <Object/3D/SkyDome/SkyDomeFactory.h>
#include <Object/3D/StageManager/StageManager.h>



//****************************************
// プロパティ定義
//****************************************
bool GameScene::getIsClear() 
{ 
	return is_clear_; 
}



void GameScene::setIsClear(bool value) 
{ 
	is_clear_ = value; 
}



int GameScene::getScore() 
{ 
	return score_; 
}



void GameScene::setScore(int value) 
{ 
	score_ = value; 
}



int GameScene::getGameOver() 
{ 
	return game_over_; 
}



void GameScene::setGameOver(int value) 
{
	game_over_ = value; 
}



StageManager* GameScene::getpStageManager()
{
	return stage_manager_;
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