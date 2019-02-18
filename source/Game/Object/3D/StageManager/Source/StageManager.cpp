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

#include <GameEngine/Input/InputManager/InputManager.h>
#include <Object/3D/Player/PlayerFactory.h>
#include <Object/3D/Balloon/BalloonGroupFactory.h>



//****************************************
// プロパティ定義
//****************************************
void StageManager::setPlayerCamera(Camera* value)
{
	player_->setCamera(value);
}



Player* StageManager::getpPlayer()
{
	return player_;
}



//****************************************
// 関数定義
//****************************************
void StageManager::Init()
{
	// 基底クラスの初期化
	//setIsUpdate(false);
	GameObjectBase::Init(nullptr, nullptr);
}



void StageManager::Uninit()
{
	UninitComponent();
}

void StageManager::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE))
	{
		player_->setIsUpdate(false);
	}
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_B))
	{
		player_->setIsUpdate(true);
	}
}



void StageManager::CreateStage()
{
	// 風船群作成
	BalloonGroupFactory balloon_group_factory;
	balloon_group_ = balloon_group_factory.Create(5);

	// プレイヤー
	PlayerFactory player_factory;
	player_ = player_factory.Create();
	player_->setBalloonGroup(balloon_group_);
}