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
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// 定数定義
//****************************************
const float BalloonUpdate::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(50.0f);



//****************************************
// 関数定義
//****************************************
void BalloonUpdate::Init()
{
	// ダウンキャスト
	balloon_ = (Balloon*)getpGameObject();

	// 剛体設定
	//balloon_->CreatePhysics();
	//balloon_->getpPhysics()->setMaxVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(300.0f));
	//balloon_->getpPhysics()->setMass(8.0f);
	//balloon_->getpPhysics()->setMyFriction(1.0f);
	//balloon_->getpPhysics()->setMyBounciness(1.0f);
}



void BalloonUpdate::Update()
{
	
}