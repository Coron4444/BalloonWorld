//================================================================================
//!	@file	 Transform.h
//!	@brief	 変形Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_TRANSFORM_H_
#define _TRANSFORM_H_



//****************************************
// インクルード文
//****************************************
#include "../Vector3D.h"
#include "../AxisVector/AxisVector.h"
#include "../MatrixExtend/MatrixExtend.h"
#include "../LimitedPointerArray/LimitedPointerArray.h"



//************************************************************														   
//! @brief   変形Class
//!
//! @details オブジェクトの変形を表すClass
//************************************************************
class Transform
{
//====================
// 変数
//====================
private:
	Vector3D position_;						//!< 座標
	Vector3D scale_;						//!< 拡縮
	Quaternion now_quaternion_;				//!< 現在のクォータニオン
	Quaternion yaw_pitch_roll_quaternion_;	//!< YawPitchRollクォータニオン
	Quaternion target_quaternion_;			//!< ターゲットクォータニオン
	Quaternion old_target_quaternion_;		//!< 古いターゲットクォータニオン
	Vector3D yaw_pitch_roll_angle_;			//!< YawPitchRoll角度
	float look_at_speed_;					//!< 向く速度
	float look_at_change_amount_;			//!< 向く変化量
	MatrixExtend matrix_extend_;			//!< 行列
	AxisVector axis_vector_;				//!< 軸


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpPosition() { return &position_; }

	//----------------------------------------
	//! @brief 拡縮取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpScale() { return &scale_; }

	//----------------------------------------
	//! @brief Pitch角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Pitch角度
	//----------------------------------------
	float* getpAnglePitch();

	//----------------------------------------
	//! @brief Yaw角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Yaw角度
	//----------------------------------------
	float* getpAngleYaw();

	//----------------------------------------
	//! @brief Roll角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Roll角度
	//----------------------------------------
	float* getpAngleRoll();

	//----------------------------------------
	//! @brief YawPitchRoll角度取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* YawPitchRoll角度
	//----------------------------------------
	Vector3D* getpAngleYawPitchRoll();

	//----------------------------------------
	//! @brief 向く速度取得関数
	//! @details
	//! @param void なし
	//! @retval float* 向く速度
	//----------------------------------------
	float* getpLookAtSpeed();

	//----------------------------------------
	//! @brief 向くベクトル設定関数
	//! @details
	//! @param look_at_vector 向くベクトル
	//! @retval void なし
	//----------------------------------------
	void setLookAtVector(Vector3D look_at_vector);

	//----------------------------------------
	//! @brief ターゲットクォータニオン設定関数
	//! @details
	//! @param axis  軸
	//! @param angle 角度
	//! @retval void なし
	//----------------------------------------
	void setTargetQuaternion(Vector3D axis, float angle);

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ関数
	//! @details
	//! @param void なし
	//----------------------------------------
	Transform();

	//----------------------------------------
	//! @brief デストラクタ関数
	//! @details
	//! @param void なし
	//----------------------------------------
	~Transform();

	

	
	
	
	
	// 軸
	void UpdateAxisVector();
	const Vector3D* GetForawrd(){return axis_vector_.GetForawrd();}
	const Vector3D* GetUp(){return axis_vector_.GetUp();}
	const Vector3D* GetRight(){return axis_vector_.GetRight();}
	AxisVector* GetAxisVector(){return &axis_vector_;}

	// 行列
	void UpdateWorldMatrixSRT();
	void UpdateWorldMatrixISRT();
	void UpdateInverseMatrix(const MATRIX* matrix){matrix_extend_.UpdateInverseMatrix(matrix);}
	void UpdateTransposeMatrix(const MATRIX* matrix){matrix_extend_.UpdateTransposeMatrix(matrix);}
	void TransposeMatrixTranslationOff(){matrix_extend_.TransposeMatrixTranslationOff();}
	MATRIX* getpWorldMatrix(){return matrix_extend_.GetWorldMatrix();}
	MatrixExtend* getpMatrixExtend(){return &matrix_extend_;}

	// 全体
	void UpdateAxisVector_WorldMatrixSRT();
	void UpdateAxisVector_WorldMatrixISRT();


//------------------------------------------------------------
private :
	// 回転
	void CreateQuaternion();

};



#endif