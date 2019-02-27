//================================================================================
//!	@file	 GameObjectBase.cpp
//!	@brief	 ゲームオブジェクトBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/03/22
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameObjectBase.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObjectManager/UpdateManager.h"
#include "../../Draw/DrawBase.h"
#include "../../Draw/DrawManager/DrawManager.h"
#include "../../Collision/CollisionBase.h"
#include "../../Collision/CollisionManager/CollisionManager.h"



//****************************************
// プロパティ定義
//****************************************
Transform* GameObjectBase::getpTransform()
{
	return &transform_;
}



Physics* GameObjectBase::getpPhysics()
{
	return physics_;
}



bool GameObjectBase::getIsInput()
{
	return is_input_;
}



void GameObjectBase::setIsInput(bool value)
{
	is_input_ = value;
}



bool GameObjectBase::getIsUpdate()
{
	return is_update_;
}



void GameObjectBase::setIsUpdate(bool value)
{
	if (is_update_ == value) return;
	is_update_ = value;
	if (is_update_)
	{
		GameObjectManager::getpInstance()
			->getpUpdateManager()->AddGameObjectBase(this);
	}
	else
	{
		GameObjectManager::getpInstance()
			->getpUpdateManager()->ReleaseGameObjectBase(this);
	}
}



void GameObjectBase::setAllComponent(DrawBase* draw, CollisionBase* collision)
{
	setDraw(draw);
	setCollision(collision);
}



DrawBase* GameObjectBase::getpDraw()
{
	return draw_;
}



void GameObjectBase::setDraw(DrawBase* value)
{
	draw_ = value;
}



CollisionBase* GameObjectBase::getpCollision()
{
	return collision_;
}



void GameObjectBase::setCollision(CollisionBase* value)
{
	collision_ = value;
}



//****************************************
// 関数定義
//****************************************
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	draw_(nullptr),
	collision_(nullptr)
{
}



GameObjectBase::~GameObjectBase()
{
	SafeRelease::Normal(&draw_);
	SafeRelease::Normal(&collision_);
	SafeRelease::Normal(&physics_);
}



void GameObjectBase::Init(DrawBase* draw, CollisionBase* collision)
{
	// 描画共通データ設定
	AddDrawCommonData(draw);

	// コンポーネント初期化
	setAllComponent(draw, collision);
	InitComponent();

	// オブジェクトマネージャーに登録
	if (!is_registration_) return;
	GameObjectManager::getpInstance()->AddGameObjectBase(this);
}



void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics();
	physics_->setGameObject(this);
}



void GameObjectBase::UninitComponent()
{
	if (draw_ != nullptr)
	{
		draw_->Uninit();
	}

	if (collision_ != nullptr)
	{
		collision_->Uninit();
	}
}



void GameObjectBase::ResetComponent()
{
	if (draw_ != nullptr)
	{
		draw_->Reset();
	}

	if (collision_ != nullptr)
	{
		collision_->Reset();
	}
}



void GameObjectBase::InitComponent()
{
	if (draw_ != nullptr)
	{
		draw_->setGameObject(this);
		draw_->Init();
	}

	if (collision_ != nullptr)
	{
		collision_->setGameObject(this);
		collision_->Init();
	}
}



void GameObjectBase::AddDrawCommonData(DrawBase* draw)
{
	if (draw == nullptr) return;
	draw->setDrawCommonData(GameObjectManager::getpInstance()
							->getpDrawManager()->getpDrawCommonData());
}