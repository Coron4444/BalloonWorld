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



//****************************************
// プロパティ定義
//****************************************
GameScene* Player::getpGameScene()
{
	return game_scene_;
}



//****************************************
// 関数定義
//****************************************
void Player::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision,
				  GameScene* game_scene)
{
	// 各種代入
	game_scene_ = game_scene;

	// 基底クラスの初期化
	GameObjectBase::Init(update, draw, collision);
}