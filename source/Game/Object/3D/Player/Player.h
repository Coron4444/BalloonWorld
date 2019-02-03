//================================================================================
//!	@file	 Player.h
//!	@brief	 プレイヤー生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================
#ifndef	_PLAYER_H_
#define _PLAYER_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   プレイヤーClass
//!
//! @details プレイヤーのClass
//************************************************************
class Player : public GameObjectNull
{
//====================
// 変数
//====================
private:
	GameScene* game_scene_ = nullptr;			//!< ゲームシーン


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ゲームシーン取得関数
	//! @details
	//! @param void なし
	//! @retval GameScene* ゲームシーン
	//----------------------------------------
	GameScene* getpGameScene();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *update     更新基底クラス
	//! @param *draw       描画基底クラス
	//! @param *collision  衝突基底クラス
	//! @param *game_scene ゲームシーン
	//! @retval void なし
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision, 
			  GameScene* game_scene);
};



#endif