//================================================================================
//!	@file	 MatrixGroup.h
//!	@brief	 行列群Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/16
//================================================================================
#ifndef	_MATRIX_GROUP_H_
#define _MATRIX_GROUP_H_



//****************************************
// インクルード文
//****************************************
#include "Vector3D.h"



//************************************************************														   
//! @brief   行列群Class
//!
//! @details 行列の集合体Class
//************************************************************
class MatrixGroup
{
//====================
// 変数
//====================
private:
	MATRIX position_;		//!< 座標行列
	MATRIX scale_;			//!< 拡縮行列
	MATRIX rotation_;		//!< 回転行列
	MATRIX inverse_;		//!< 逆行列
	MATRIX transpose_;		//!< 転置行列
	MATRIX world_;			//!< ワールド行列


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 座標行列
	//----------------------------------------
	MATRIX* getpPositionMatrix();

	//----------------------------------------
	//! @brief 座標行列設定関数
	//! @details
	//! @param value 行列にしたい座標値
	//! @retval void なし
	//----------------------------------------
	void setPositionMatrix(Vec3* value);

	//----------------------------------------
	//! @brief 拡縮行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 拡縮行列
	//----------------------------------------
	MATRIX* getpScaleMatrix();

	//----------------------------------------
	//! @brief 拡縮行列設定関数
	//! @details
	//! @param value 行列にしたい拡縮値
	//! @retval void なし
	//----------------------------------------
	void setScaleMatrix(Vec3* value);

	//----------------------------------------
	//! @brief 回転行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 拡縮行列
	//----------------------------------------
	MATRIX* getpRotationMatrix();

	//----------------------------------------
	//! @brief 回転行列設定関数
	//! @details
	//! @param value 行列にしたい回転値
	//! @retval void なし
	//----------------------------------------
	void setRotationMatrix(Quaternion* value);

	//----------------------------------------
	//! @brief 逆行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 逆行列
	//----------------------------------------
	MATRIX* getpInverseMatrix();

	//----------------------------------------
	//! @brief 逆行列設定関数
	//! @details
	//! @param value 逆行列にしたい行列
	//! @retval void なし
	//----------------------------------------
	void setInverseMatrix(MATRIX* value);

	//----------------------------------------
	//! @brief 転置行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 転置行列
	//----------------------------------------
	MATRIX* getpTransposeMatrix();

	//----------------------------------------
	//! @brief 転置行列設定関数
	//! @details
	//! @param value           転置行列にしたい行列
	//! @param is_position_off 平行移動OFFフラグ
	//! @retval void なし
	//----------------------------------------
	void setTransposeMatrix(MATRIX* value, bool is_position_off = false);

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param void
	//! @retval MATRIX* 転置行列
	//----------------------------------------
	MATRIX* getpWorldMatrix();

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	MatrixGroup();

	//----------------------------------------
	//! @brief ワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrix();

	//----------------------------------------
	//! @brief 逆行列付きワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief 転置行列付きワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrixPlusTranspose();

	//----------------------------------------
	//! @brief ワールド行列に親行列追加関数
	//! @details
	//! @param parent_matrix 親の行列
	//! @retval void なし
	//----------------------------------------
	void AddParentMatrixToWorldMatrix(MATRIX* parent_matrix);

private:
	//----------------------------------------
	//! @brief 全行列リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetAllMatrix();
};



#endif