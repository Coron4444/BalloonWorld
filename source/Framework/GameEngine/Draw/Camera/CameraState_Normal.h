//================================================================================
//!	@file	 CameraState_Normal.h
//!	@brief	 ノーマルカメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_CAMERA_STATE_NORMAL_H_
#define _CAMERA_STATE_NORMAL_H_



//****************************************
// インクルード文
//****************************************
#include "Camera.h"



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   ノーマルカメラステートClass
//!
//! @details ノーマルのカメラステートClass
//************************************************************
class CameraState_Normal : public Camera::State
{
//====================
// 定数
//====================
public:
	static const float TRANSLATION_SPEED;	//!< 速度
	static const float ROTATION_SPEED;		//!< 回転速度
	static const float POSITION_Y;			//!< Y座標
	static const float GAZING_POINT_Y;		//!< 注視点のY座標


//====================
// 変数
//====================
private:
	Vector3D lenght_;							//!< 距離
	float rotation_speed_;						//!< 回転速度


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
	//! @brief 平行移動入力関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief 回転入力関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputRotation();
};



#endif