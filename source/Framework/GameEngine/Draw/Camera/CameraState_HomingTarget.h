//================================================================================
//!	@file	 CameraState_HomingTarget.h
//!	@brief	 ターゲット追跡カメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_STATE_HOMING_TARGET_H_
#define _CAMERA_STATE_HOMING_TARGET_H_



//****************************************
// インクルード文
//****************************************
#include "Camera.h"



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   ターゲット追跡カメラステートClass
//!
//! @details ターゲット追跡のカメラステートClass
//************************************************************
class CameraState_HomingTarget : public Camera::State
{
//====================
// 定数
//====================
public:
	static const Vec3 DEFAULT_LENGHT;			//!< 既定距離
	static const float GAZING_POINT_Y;			//!< 注視点のY座標
	static const float DEFAULT_ROTATION_SPEED;	//!< 既定回転速度


//====================
// 変数
//====================
private:
	GameObjectBase* target_object_ = nullptr;	//!< ターゲットオブジェクト
	Vector3D lenght_;							//!< 距離
	float rotation_speed_;						//!< 回転速度


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ターゲットオブジェクト設定関数
	//! @details
	//! @param value ターゲットオブジェクト
	//! @retval void なし
	//----------------------------------------
	void setTargetObject(GameObjectBase* value);

	//----------------------------------------
	//! @brief 距離設定関数
	//! @details
	//! @param value 距離
	//! @retval void なし
	//----------------------------------------
	void setLength(Vec3 value);

	//----------------------------------------
	//! @brief 回転速度設定関数
	//! @details
	//! @param value 回転速度
	//! @retval void なし
	//----------------------------------------
	void setRotationSpeed(float value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param camera カメラ
	//! @retval void なし
	//----------------------------------------
	void Init() override;

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

private:
	//----------------------------------------
	//! @brief 座標算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationPosition();

	//----------------------------------------
	//! @brief 注視点算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationGazingPoint();

	//----------------------------------------
	//! @brief 前ベクトル算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationForward();

	//----------------------------------------
	//! @brief 注視点軸関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputRotationAroundGazingPoint();
};



#endif