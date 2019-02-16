//================================================================================
//!	@file	 Axis.h
//!	@brief	 軸Class
//! @details 
//!	@author  Kai Araki									@date 2018/01/08
//================================================================================
#ifndef	_AXIS_H_
#define _AXIS_H_



//****************************************
// インクルード文
//****************************************
#include "Vector3D.h"



//************************************************************														   
//! @brief   軸Class
//!
//! @details 軸を表すClass
//************************************************************
class Axis
{
//====================
// 定数
//====================
private:
	static const Vector3D DEFAULT_FORWARD;	//!< 既定前ベクトル
	static const Vector3D DEFAULT_UP;		//!< 既定上ベクトル
	static const Vector3D DEFAULT_RIGHT;	//!< 既定右ベクトル


//====================
// 変数
//====================
private:
	Vector3D forward_ = DEFAULT_FORWARD;			//!< 前ベクトル
	Vector3D default_forward_ = DEFAULT_FORWARD;	//!< 既定前ベクトル
	Vector3D up_ = DEFAULT_UP;						//!< 上ベクトル
	Vector3D default_up_ = DEFAULT_UP;				//!< 既定上ベクトル
	Vector3D right_ = DEFAULT_RIGHT;				//!< 右ベクトル
	Vector3D default_right_ = DEFAULT_RIGHT;		//!< 既定右ベクトル


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 前ベクトル
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief 既定前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定前ベクトル
	//----------------------------------------
	Vector3D* getpDefaultForward();

	//----------------------------------------
	//! @brief 前ベクトル設定関数
	//! @details
	//! @param value 前ベクトル
	//! @retval void なし
	//----------------------------------------
	void setForward(Vec3 value);

	//----------------------------------------
	//! @brief 上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 上ベクトル
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief 既定上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定上ベクトル
	//----------------------------------------
	Vector3D* getpDefaultUp();

	//----------------------------------------
	//! @brief 右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 右ベクトル
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief 既定右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定右ベクトル
	//----------------------------------------
	Vector3D* getpDefaultRight();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief X軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief 前ベクトル軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisForward(float radian);

	//----------------------------------------
	//! @brief 上ベクトル軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisUp(float radian);

	//----------------------------------------
	//! @brief 右ベクトル軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisRight(float radian);

	//----------------------------------------
	//! @brief 任意軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void RotationAxisAny(Vec3 axis, float radian);

	//----------------------------------------
	//! @brief 行列回転関数
	//! @details
	//! @param rotation_matrix 行列
	//! @retval void なし
	//----------------------------------------
	void RotationMatrix(MATRIX* rotation_matrix);

	//----------------------------------------
	//! @brief クォータニオン回転回転関数
	//! @details
	//! @param quaternion クォータニオン
	//! @retval void なし
	//----------------------------------------
	void RotationQuaternion(Quaternion* quaternion);

private:
	//----------------------------------------
	//! @brief 上&右ベクトル算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationUpAndRightVector();

	//----------------------------------------
	//! @brief 全ベクトル正規化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void NormalizeAllVector();
};



#endif