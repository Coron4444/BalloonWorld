//================================================================================
//!	@file	 GameScene.cpp
//!	@brief	 �Q�[���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
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
// �v���p�e�B��`
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



//****************************************
// �֐���`
//****************************************
GameScene::GameScene(StateBase* state)
	: SceneNull(state) 
{
}



void GameScene::Init()
{
	// �R�C���̍쐬
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

	// �X�J�C�h�[��
	SkyDomeFactory sky_dome_factory;
	sky_dome_factory.Create();

	// �t�B�[���h
	FieldFactory field_factory;
	Field* field = field_factory.Create();
	GameObjectManager::getpInstance()->getpCollisionManager()
		->setGround(field->getpMeshPlanePolygon());

	// �X�e�[�W
	stage_manager_ = new StageManager();
	stage_manager_->Init();
	stage_manager_->CreateStage();
	
	// �G
	EnemyFactory enemy_factory;
	Enemy* temp2 = enemy_factory.Create();
	*temp2->getpTransform()->getpPosition() = Vec3(-5.0f, 6.0f, 5.0f);
	*temp2->getpTransform()->getpScale() = Vec3(3.0f, 3.0f, 3.0f);
	//*temp2->getpTransform()->getpAngleYaw() += 3.0f;
	temp2->getpTransform()->CreateWorldMatrix();

	// �S�[��
	GoalFactory goal_factory;
	Goal* temp3 = goal_factory.Create();
	*temp3->getpTransform()->getpPosition() = Vec3(10.0f, 0.0f, 20.0f);
	temp3->getpTransform()->CreateWorldMatrix();

	// �X�R�A
	//ScoreFactory score_factory;
	//score_factory.Create(this);

	// �X�e�[�g������
	SceneNull::Init();
}