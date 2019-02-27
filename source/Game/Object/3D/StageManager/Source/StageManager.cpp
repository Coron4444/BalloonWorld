//================================================================================
//!	@file	 StageManager.h
//!	@brief	 ステージマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StageManager.h"

#include <Object/3D/Balloon/BalloonGroupFactory.h>
#include <Object/3D/Player/PlayerFactory.h>
#include <Object/3D/Needle/NeedleFactory.h>
#include <Object/3D/Field/FieldFactory.h>
#include <Object/3D/SkyDome/SkyDomeFactory.h>
#include <Object/3D/StartBlock/StartBlockFactory.h>
#include <Object/3D/Scaffold/ScaffoldFactory.h>



//****************************************
// 定数定義
//****************************************
const int StageManager::MAX_TIME = TimeToFrame::SecondToFrame(60.0f);
const int StageManager::BONUS_SCORE = 300;
const int StageManager::BONUS_SCORE_RAITO = 2;



//****************************************
// プロパティ定義
//****************************************
bool StageManager::getIsEnable()
{
	return is_enable_;
}



void StageManager::setIsEnable(bool value)
{
	if (value)
	{
		if (is_enable_) return;
		is_enable_ = true;
		setIsUpdate(true);
		setIsInput(true);
		player_->setIsUpdate(true);
		//player_->getpCamera()->getpState()->setIsUpdate(true);
		player_->getpCollision()->setIsEnable(true);
	}
	else
	{
		is_enable_ = false;
		setIsUpdate(false);
		setIsInput(false);
		player_->setIsUpdate(false);
		//player_->getpCamera()->getpState()->setIsUpdate(false);
		player_->getpCollision()->setIsEnable(false);
	}
}



int StageManager::getScore()
{
	return score_;
}



int StageManager::getTime()
{
	return (int)TimeToFrame::FrameToSecond(time_);
}



int StageManager::getBalloonNum()
{
	return player_->getpBalloonGroup()->getRemainingBalloonNum();
}



void StageManager::setPlayerCamera(Camera* value)
{
	player_->setCamera(value);
}



Player* StageManager::getpPlayer()
{
	return player_;
}



bool StageManager::getIsOnTheGround()
{
	return player_->getIsOnTheGround();
}



//****************************************
// 関数定義
//****************************************
void StageManager::Init()
{
	score_ = 0;
	time_ = MAX_TIME;

	// 基底クラスの初期化
	GameObjectBase::Init(nullptr, nullptr);
}



void StageManager::Uninit()
{
	UninitComponent();
}



void StageManager::Update()
{
	score_ += player_->getScore();

	// タイマー
	time_--;
	if (time_ < 0)
	{
		time_ = 0;
		return;
	}

	// 着地ボーナス
	if (!player_->getIsOnTheGround()) return;
	if (is_ground_) return;
	is_ground_ = true;
	score_ += BONUS_SCORE + BONUS_SCORE_RAITO * (int)TimeToFrame::FrameToSecond(time_);
}



void StageManager::CreateStage()
{
	// スカイドーム
	SkyDomeFactory sky_dome_factory;
	sky_dome_factory.Create();

	// フィールド
	FieldFactory field_factory;
	Field* field = field_factory.Create();
	GameObjectManager::getpInstance()->getpCollisionManager()
		->setGround(field->getpMeshPlanePolygon());

	// 風船群作成
	BalloonGroupFactory balloon_group_factory;
	balloon_group_ = balloon_group_factory.Create(5, Vector3D(0.0f, 313.0f, 0.0f));

	// プレイヤー
	PlayerFactory player_factory;
	player_ = player_factory.Create();
	player_->setPosition(Vector3D(0.0f, 303.0f, 0.0f));
	player_->setBalloonGroup(balloon_group_);

	// スタートブロック
	StartBlockFactory start_block_factory;
	start_block_ = start_block_factory.Create();
	start_block_->setPosition(Vector3D(0.0f, 300.0f, 0.0f));

	ScaffoldFactory scaffold_factory;
	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(00.0f, 00.0f, 0.0f));
	scaffold_->setScale(Vector3D(3.0f, 50.0f, 3.0f));
	scaffold_->setColor(XColor4(1.0f, 0.0f, 1.0f, 1.0f));
	scaffold_->setScore(50);

	/*
	// 足場
	ScaffoldFactory scaffold_factory;
	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(30.0f, 250.0f, 0.0f));
	scaffold_->setScale(Vector3D(3.0f, 50.0f, 3.0f));
	scaffold_->setColor(XColor4(1.0f, 0.0f, 1.0f, 1.0f));
	scaffold_->setScore(50);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(30.0f, 280.0f, -10.0f));
	scaffold_->setScale(Vector3D(10.0f, 10.0f, 10.0f));
	scaffold_->setColor(XColor4(1.0f, 1.0f, 3.0f, 1.0f));
	scaffold_->setScore(10);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(-60.0f, 50.0f, -70.0f));
	scaffold_->setScale(Vector3D(10.0f, 10.0f, 10.0f));
	scaffold_->setColor(XColor4(1.0f, 1.0f, 3.0f, 1.0f));
	scaffold_->setScore(10);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(-20.0f, 50.0f, 60.0f));
	scaffold_->setScale(Vector3D(10.0f, 10.0f, 10.0f));
	scaffold_->setColor(XColor4(1.0f, 1.0f, 3.0f, 1.0f));
	scaffold_->setScore(10);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(-90.0f, 135.0f, -64.0f));
	scaffold_->setScale(Vector3D(10.0f, 30.0f, 10.0f));
	scaffold_->setColor(XColor4(1.0f, 1.0f, 3.0f, 1.0f));
	scaffold_->setScore(10);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(-60.0f, 50.0f, -70.0f));
	scaffold_->setScale(Vector3D(10.0f, 10.0f, 10.0f));
	scaffold_->setColor(XColor4(1.0f, 1.0f, 3.0f, 1.0f));
	scaffold_->setScore(10);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(60.0f, 100.0f, -40.0f));
	scaffold_->setScale(Vector3D(60.0f, 5.0f, 3.0f));
	scaffold_->setColor(XColor4(0.0f, 0.0f, 1.0f, 1.0f));
	scaffold_->setScore(30);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(10.0f, 200.0f, -40.0f));
	scaffold_->setScale(Vector3D(5.0f, 10.0f, 5.0f));
	scaffold_->setColor(XColor4(0.0f, 0.5f, 1.0f, 1.0f));
	scaffold_->setScore(30);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(30.0f, 170.0f, -10.0f));
	scaffold_->setScale(Vector3D(5.0f, 10.0f, 5.0f));
	scaffold_->setColor(XColor4(0.0f, 0.5f, 1.0f, 1.0f));
	scaffold_->setScore(30);

	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vector3D(80.0f, 30.0f, -40.0f));
	scaffold_->setScale(Vector3D(5.0f, 10.0f, 5.0f));
	scaffold_->setColor(XColor4(0.0f, 0.5f, 1.0f, 1.0f));
	scaffold_->setScore(30);

	Random::getpInstance()->getFloat(-100.0f, 100.0f);
	int object_num = 200;
	float hani = 250.0f;
	for (int i = 0; i < object_num; i++)
	{
		scaffold_ = scaffold_factory.Create();
		scaffold_->setPosition(Vector3D(Random::getpInstance()->getFloat(-hani, hani),
									Random::getpInstance()->getFloat(10.0f, 270.0f),
									Random::getpInstance()->getFloat(-hani, hani)));
		scaffold_->setScale(Vector3D(Random::getpInstance()->getFloat(1.0f, 30.0f), 
								 Random::getpInstance()->getFloat(10.0f, 50.0f),
								 Random::getpInstance()->getFloat(1.0f, 30.0f)));
		scaffold_->setColor(XColor4(Random::getpInstance()->getFloat(0.0f, 1.0f), 
									Random::getpInstance()->getFloat(0.0f, 1.0f), 
									Random::getpInstance()->getFloat(0.0f, 1.0f), 1.0f));
		scaffold_->setScore((int)(scaffold_->getpTransform()->getpScale()->x + scaffold_->getpTransform()->getpScale()->z));
	}

	// 棘
	NeedleFactory needle_factory;
	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vector3D(-40.0f, 250.0f, -30.0f));
	needle_->setScale(3.0f);

	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vector3D(50.0f, 200.0f, -30.0f));
	needle_->setScale(5.0f);

	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vector3D(10.0f, 150.0f, 30.0f));
	needle_->setScale(3.0f);

	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vector3D(-100.0f, 100.0f, 60.0f));
	needle_->setScale(5.0f);

	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vector3D(70.0f, 50.0f, 80.0f));
	needle_->setScale(3.0f);

	for (int i = 0; i < object_num; i++)
	{
		needle_ = needle_factory.Create(new NeedleState_Loop());
		needle_->setPosition(Vector3D(Random::getpInstance()->getFloat(-hani, hani),
								  Random::getpInstance()->getFloat(10.0f, 270.0f),
								  Random::getpInstance()->getFloat(-hani, hani)));
		needle_->setScale(Random::getpInstance()->getFloat(2.0f, 10.0f));
	}
	*/
}