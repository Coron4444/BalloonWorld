//================================================================================
//!	@file	 BalloonUpdate.cpp
//!	@brief	 風船更新Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonUpdate.h"
#include "../Balloon.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <Tool/MeterToFrame.h>
#include <Tool/Random.h>


//****************************************
// 定数定義
//****************************************
const float BalloonUpdate::RISING_SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(1000000.0f);



//****************************************
// 関数定義
//****************************************
void BalloonUpdate::Init()
{
	// ダウンキャスト
	balloon_ = (Balloon*)getpGameObject();
}



void BalloonUpdate::Update()
{
	// 上昇
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)
		->getpRigidBody()->activate();
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)
		->AddAcceleration(Vec3(0.0f, RISING_SPEED, 0.0f),
						  Vec3(0.0f, 1.0f, 0.0f));
}