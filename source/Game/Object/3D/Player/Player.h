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
class BulletPhysicsObject;
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
	static const float ACCELERATION;	//!< 加速度


//====================
// 変数
//====================
private:
	GameScene* game_scene_ = nullptr;				//!< ゲームシーン
	BalloonGroup* balloon_group_ = nullptr;			//!< 風船群
	Camera* camera_ = nullptr;						//!< カメラ
	BulletPhysicsObject* bullet_object_ = nullptr;	//!< バレットオブジェクト


//====================
// プロパティ
//====================
public:
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
	//! @param *draw      描画基底クラス
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief 平行移動入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief カメラ無し平行移動入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputTranslationNotCamera();
};



#endif