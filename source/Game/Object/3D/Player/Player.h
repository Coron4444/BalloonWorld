//================================================================================
//!	@file	 Player.h
//!	@brief	 プレイヤーClass
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



//****************************************
// クラス宣言
//****************************************
class BalloonGroup;
class Camera;



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
	BalloonGroup* balloon_group_ = nullptr;		//!< 風船群
	Camera* camera_ = nullptr;					//!< カメラ

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

	//----------------------------------------
	//! @brief ゲームシーン設定関数
	//! @details
	//! @param *value ゲームシーン
	//! @retval void なし
	//----------------------------------------
	void setGameScene(GameScene* value);

	//----------------------------------------
	//! @brief 風船群取得関数
	//! @details
	//! @param void なし
	//! @retval BalloonGroup* 風船群
	//----------------------------------------
	BalloonGroup* getpBalloonGroup();

	//----------------------------------------
	//! @brief 風船群設定関数
	//! @details
	//! @param *value 風船群
	//! @retval void なし
	//----------------------------------------
	void setBalloonGroup(BalloonGroup* value);

	//----------------------------------------
	//! @brief カメラ取得関数
	//! @details
	//! @param void なし
	//! @retval Camera* カメラ
	//----------------------------------------
	Camera* getpCamera();

	//----------------------------------------
	//! @brief カメラ設定関数
	//! @details
	//! @param *value カメラ
	//! @retval void なし
	//----------------------------------------
	void setCamera(Camera* value);

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

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;
};



#endif