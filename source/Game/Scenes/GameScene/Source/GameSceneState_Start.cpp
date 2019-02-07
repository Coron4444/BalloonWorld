//================================================================================
//!	@file	 GameSceneState_Start.cpp
//!	@brief	 �Q�[���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameSceneState_Start.h"
#include "../GameScene.h"

#include <GameEngine/Draw/DrawManager/DrawManager.h>
#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/SafeRelease.h>

#include <Object/2D/Score/ScoreFactory.h>
#include <Object/3D/Coin/CoinFactory.h>
#include <Object/3D/Enemy/EnemyFactory.h>
#include <Object/3D/Field/FieldFactory.h>
#include <Object/3D/Goal/GoalFactory.h>
#include <Object/3D/SkyDome/SkyDomeFactory.h>
#include <Object/3D/Player/PlayerFactory.h>
#include <Object/3D/StencilShadowTest/StencilShadowTestFactory.h>
#include <Object/3D/Balloon/BalloonFactory.h>

#include <Scenes/ResultScene/ResultScene.h>
#include <Scenes/ResultScene/ResultSceneState_Start.h>



//****************************************
// �֐���`
//****************************************
void GameSceneState_Start::Init()
{
	// �Q�[���V�[���̎擾
	game_scene_ = (GameScene*)getpScene();

	// �Q�[���V�[�����ʃf�[�^�[�̏�����
	game_scene_->setIsClear(false);
	game_scene_->setScore(0);

	// �f�t�H���g�J�����̍쐬
	Camera* camera = GameObjectManager::getpInstance()->getpDrawManager()
		->getpCamera(DrawManager::RenderTargetType::MAIN);
	camera->setState(new CameraState_CrawlUp());

	//GameObjectManager::GetDrawManager()->GetBackBuffer()
	//	->GetCamera()->ChangeState(new CameraState_HomingTarget());

	// �R�C���̍쐬
	//CoinFactory coin_factory;
	//Coin* temp = coin_factory.Create();
	//*temp->getpTransform()->getpPosition() = Vec3(5.0f, 0.0f, 0.0f);
	//temp->getpTransform()->CreateWorldMatrix();
	//
	//temp = coin_factory.Create();
	//*temp->getpTransform()->getpPosition() = Vec3(5.0f, 0.0f, 5.0f);
	//temp->getpTransform()->CreateWorldMatrix();
	//
	//temp = coin_factory.Create();
	//*temp->getpTransform()->getpPosition() = Vec3(-5.0f, 0.0f, -5.0f);
	//temp->getpTransform()->CreateWorldMatrix();

	// �X�J�C�h�[��
	//SkyDomeFactory sky_dome_factory;
	//sky_dome_factory.Create();


	// �t�B�[���h
	FieldFactory field_factory;
	Field* field = field_factory.Create();
	GameObjectManager::getpInstance()->getpCollisionManager()
		->setGround(field->getpMeshPlanePolygon());
	
	//StencilShadowTestFactory stencil_factory;
	//stencil_factory.Create();

	// �v���C���[
	PlayerFactory player_factory;
	/*Player* player = */player_factory.Create(game_scene_);

	//((CameraState_HomingTarget*)GameObjectManager::GetDrawManager()->GetBackBuffer()
	//	->GetCamera()->GetCameraState())->SetTarget(player);

	// �G
	//EnemyFactory enemy_factory;
	//Enemy* temp2 = enemy_factory.Create();
	//*temp2->getpTransform()->getpPosition() = Vec3(-5.0f, 0.0f, 5.0f);
	//temp2->getpTransform()->CreateWorldMatrix();
	
	// ���D�쐬
	//BalloonFactory balloon_factory;
	//balloon_factory.Create();

	// �S�[��
	//GoalFactory goal_factory;
	//Goal* temp3 = goal_factory.Create();
	//*temp3->getpTransform()->getpPosition() = Vec3(10.0f, 0.0f, 20.0f);
	//temp3->getpTransform()->CreateWorldMatrix();
	
	// �X�R�A
	ScoreFactory score_factory;
	score_factory.Create(game_scene_);
}



void GameSceneState_Start::Update()
{
	// �N���A
	if (game_scene_->getGameOver() == 0)
	{
		game_scene_->getpSceneManager()->getpCommonData()->setIsClear(true);
		game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
	}

	// ���s
	if (game_scene_->getGameOver() == 1)
	{
		game_scene_->getpSceneManager()->getpCommonData()->setIsClear(false);
		game_scene_->getpSceneManager()->setNextScene(new ResultScene(new ResultSceneState_Start()));
	}
}