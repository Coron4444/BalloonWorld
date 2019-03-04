//================================================================================
//!	@file	 Physics.h
//!	@brief	 物理Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/19
//================================================================================
#ifndef	_PHYSICS_H_
#define _PHYSICS_H_



//****************************************
// インクルード文
//****************************************
#include "Vector3D.h"



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   物理Class
//!
//! @details 物理の計算Class
//************************************************************
class Physics
{
//====================
// 定数
//====================
private:
	static const float VELOCITY_MIN;		//!< 最低速度


//====================
// 変数
//====================
private:
	bool is_enable_ = true;				//!< 有効フラグ
	GameObjectBase* game_object_;		//!< ゲームオブジェクト
	Vector3D acceleration_;				//!< 加速度
	Vector3D velocity_;					//!< 速度
	float max_horizontal_velocity_;		//!< 最大水平速度
	float max_vertical_velocity_;		//!< 最大垂直速度
	float mass_;						//!< 質量
	float friction_;					//!< 摩擦
	float my_friction_;					//!< 自分の摩擦
	float bounciness_;					//!< 反発力
	float my_bounciness_;				//!< 自分の反発力
	bool is_gravity_;					//!< 重力フラグ
	float gravity_acceleration_;		//!< 重力加速度
	Vector3D gravity_direction_;		//!< 重力ベクトル
	bool is_on_tha_ground_;				//!< 地面に乗っているフラグ
	bool is_landing_;					//!< 着地したフラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 有効フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval value 有効フラグ
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief 有効フラグ設定関数
	//! @details
	//! @param value 有効フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsEnable(bool value);

	//----------------------------------------
	//! @brief ゲームオブジェクト設定関数
	//! @details
	//! @param *value ゲームオブジェクト
	//! @retval void なし
	//----------------------------------------
	void setGameObject(GameObjectBase* value);

	//----------------------------------------
	//! @brief 加速度取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 加速度
	//----------------------------------------
	Vector3D* getpAcceleration();

	//----------------------------------------
	//! @brief 速度取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 速度
	//----------------------------------------
	Vector3D* getpVelocity();

	//----------------------------------------
	//! @brief 最大水平速度取得関数
	//! @details
	//! @param void なし
	//! @retval float 最大水平速度
	//----------------------------------------
	float getMaxHorizontalVelocity();

	//----------------------------------------
	//! @brief 最大水平速度設定関数
	//! @details
	//! @param value 最大水平速度
	//! @retval void なし
	//----------------------------------------
	void setMaxHorizontalVelocity(float value);

	//----------------------------------------
	//! @brief 最大垂直速度取得関数
	//! @details
	//! @param void なし
	//! @retval float 最大垂直速度
	//----------------------------------------
	float getMaxVerticalVelocity();

	//----------------------------------------
	//! @brief 最大垂直速度設定関数
	//! @details
	//! @param value 最大垂直速度
	//! @retval void なし
	//----------------------------------------
	void setMaxVerticalVelocity(float value);

	//----------------------------------------
	//! @brief 質量取得関数
	//! @details
	//! @param void なし
	//! @retval float 質量
	//----------------------------------------
	float getMass();

	//----------------------------------------
	//! @brief 質量設定関数
	//! @details
	//! @param value 質量
	//! @retval void なし
	//----------------------------------------
	void setMass(float value);

	//----------------------------------------
	//! @brief 摩擦力取得関数
	//! @details
	//! @param void なし
	//! @retval float 摩擦力
	//----------------------------------------
	float getFriction();

	//----------------------------------------
	//! @brief 自分の摩擦力取得関数
	//! @details
	//! @param void なし
	//! @retval float 自分の摩擦力
	//----------------------------------------
	float getMyFriction();

	//----------------------------------------
	//! @brief 自分の摩擦力設定関数
	//! @details
	//! @param value 自分の摩擦力
	//! @retval void なし
	//----------------------------------------
	void setMyFriction(float value);

	//----------------------------------------
	//! @brief 反発力取得関数
	//! @details
	//! @param void なし
	//! @retval float 反発力
	//----------------------------------------
	float getBounciness();

	//----------------------------------------
	//! @brief 自分の反発力取得関数
	//! @details
	//! @param void なし
	//! @retval float 自分の反発力
	//----------------------------------------
	float getMyBounciness();

	//----------------------------------------
	//! @brief 自分の反発力設定関数
	//! @details
	//! @param value 自分の反発力
	//! @retval void なし
	//----------------------------------------
	void setMyBounciness(float value);

	//----------------------------------------
	//! @brief 重力フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 重力フラグ
	//----------------------------------------
	bool getIsGravity();

	//----------------------------------------
	//! @brief 重力フラグ設定関数
	//! @details
	//! @param value 重力フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsGravity(float value);

	//----------------------------------------
	//! @brief 地面に乗っているフラグ設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void setOnTheGround();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Physics();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 摩擦力追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddFriction(float friction);

	//----------------------------------------
	//! @brief 反発力追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddBounciness(float bounciness);


private :
	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief 加速度更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAcceleration();

	//----------------------------------------
	//! @brief 速度更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateVelocity();

	//----------------------------------------
	//! @brief 座標更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdatePosition();

	//----------------------------------------
	//! @brief 重力追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddGravity();

	//----------------------------------------
	//! @brief 地面更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateGround();

	//----------------------------------------
	//! @brief 速度の最小値・最大値チェック関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CheckVelocityMinMax();

};



#endif