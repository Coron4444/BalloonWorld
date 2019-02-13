//================================================================================
//!	@file	 Player.cpp
//!	@brief	 プレイヤーClass
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Player.h"

#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Object/3D/Balloon/BalloonGroup.h>



//****************************************
// プロパティ定義
//****************************************
BalloonGroup* Player::getpBalloonGroup()
{
	return balloon_group_;
}



void Player::setBalloonGroup(BalloonGroup* value)
{
	value->getpReferenceList()->getpMyPointer(&balloon_group_);
}



Camera* Player::getpCamera()
{
	return camera_;
}



void Player::setCamera(Camera* value)
{
	camera_ = value;
}



//****************************************
// 関数定義
//****************************************
void Player::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision)
{
	// 基底クラスの初期化
	GameObjectBase::Init(update, draw, collision);
}



void Player::Uninit()
{
	GameObjectBase::Uninit();

	if (balloon_group_ == nullptr) return;
	balloon_group_->getpReferenceList()->ReleaseReference(&balloon_group_);
}