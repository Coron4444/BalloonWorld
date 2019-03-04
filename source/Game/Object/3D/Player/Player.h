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
	static const float ACCELERATION;			//!< 加速度
	static const float MAX_VERTICAL_VELOCITY;	//!< 最大垂直方向速度
	static const float MAX_MASS;				//!< 最大質量

//====================
// 変数
//====================
private:
	BalloonGroup* balloon_group_ = nullptr;			//!< 風船群
	Camera* camera_ = nullptr;						//!< カメラ
	BulletPhysicsObject* bullet_object_ = nullptr;	//!< バレットオブジェクト
	bool is_on_the_ground_ = false;					//!< 地面着地フラグ
	int score_ = 0;	
	int anim_counter_ = 0;


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vector3D value);

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

	//----------------------------------------
	//! @brief 地面着地フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 地面着地フラグ
	//----------------------------------------
	bool getIsOnTheGround();

	//----------------------------------------
	//! @brief 地面着地フラグ設定関数
	//! @details
	//! @param value 地面着地フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsOnTheGround(bool value);

	//----------------------------------------
	//! @brief スコア取得関数
	//! @details
	//! @param void なし
	//! @retval int スコア
	//----------------------------------------
	int getScore();
	
	//----------------------------------------
	//! @brief アニメーションカウント取得関数
	//! @details
	//! @param void なし
	//! @retval int アニメーションカウント
	//----------------------------------------
	int getAnimCount();

	//----------------------------------------
	//! @brief アニメーションカウント取得関数
	//! @details
	//! @param value アニメーションカウント
	//! @retval void なし
	//----------------------------------------
	void setAnimCount(int value);


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
	//void DebugDisplay() override;

	//----------------------------------------
	//! @brief スコア追加関数
	//! @details 
	//! @param value スコア
	//! @retval void なし
	//----------------------------------------
	void AddScore(int value);

private:
	//----------------------------------------
	//! @brief 入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Input();

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

	//----------------------------------------
	//! @brief 風船入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputBalloon();
};



#endif