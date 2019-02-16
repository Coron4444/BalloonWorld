//================================================================================
//!	@file	 OBB.h
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_OBB_H_
#define _OBB_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase.h"
#include "Plane.h"

#include <Tool/Axis.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   OBBClass
//!
//! @details OBBのClass
//************************************************************
class OBB : public CollisionShapeBase
{
//====================
// 定数
//====================
private:
	static const int MAX_POINT_NUM = 8;		//!< 最大点数


//====================
// 変数
//====================
private:
	Vector3D position_;				//!< 座標
	Vector3D length_;				//!< 各辺の長さ
	Axis axis_;						//!< 軸ベクトル
	Plane plane_right_;				//!< 右方向平面
	Plane plane_up_;				//!< 上方向平面
	Plane plane_forward_;			//!< 前方向平面
	Plane plane_inverse_right_;		//!< 逆右方向平面
	Plane plane_inverse_up_;		//!< 逆上方向平面
	Plane plane_inverse_forward_;	//!< 逆前方向平面


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
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief 軸取得関数
	//! @details
	//! @param void なし
	//! @retval Axis* 軸
	//----------------------------------------
	Axis* getpAxis();

	//----------------------------------------
	//! @brief 軸設定関数
	//! @details
	//! @param value 軸
	//! @retval void なし
	//----------------------------------------
	void setAxis(Axis* value);

	//----------------------------------------
	//! @brief 前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 前ベクトル
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief 前ベクトル設定関数
	//! @details
	//! @param value 前ベクトル
	//! @retval void なし
	//----------------------------------------
	void setForward(Vector3D value);

	//----------------------------------------
	//! @brief 上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 上ベクトル
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief 右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 右ベクトル
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief 各辺の取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 各辺の長さ
	//----------------------------------------
	Vector3D* getpLength();

	//----------------------------------------
	//! @brief 右長さベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 右長さベクトル
	//----------------------------------------
	Vector3D getRightLengthVector();

	//----------------------------------------
	//! @brief 上長さベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 上長さベクトル
	//----------------------------------------
	Vector3D getUpLengthVector();

	//----------------------------------------
	//! @brief 前長さベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 前長さベクトル
	//----------------------------------------
	Vector3D getForwardLengthVector();

	//----------------------------------------
	//! @brief 右長さベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 右長さベクトルの半分
	//----------------------------------------
	Vector3D getRightLengthVectorHalf();

	//----------------------------------------
	//! @brief 上長さベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 上長さベクトルの半分
	//----------------------------------------
	Vector3D getUpLengthVectorHalf();

	//----------------------------------------
	//! @brief 前長さベクトルの半分取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 前長さベクトルの半分
	//----------------------------------------
	Vector3D getForwardLengthVectorHalf();

	//----------------------------------------
	//! @brief 右方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 右方向平面
	//----------------------------------------
	Plane* getpPlaneRight();

	//----------------------------------------
	//! @brief 上方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 上方向平面
	//----------------------------------------
	Plane* getpPlaneUp();

	//----------------------------------------
	//! @brief 前方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 前方向平面
	//----------------------------------------
	Plane* getpPlaneForward();

	//----------------------------------------
	//! @brief 逆右方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 逆右方向平面
	//----------------------------------------
	Plane* getpPlaneInverseRight();

	//----------------------------------------
	//! @brief 逆上方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 逆上方向平面
	//----------------------------------------
	Plane* getpPlaneInverseUp();

	//----------------------------------------
	//! @brief 逆前方向平面取得関数
	//! @details
	//! @param void なし
	//! @retval Plane* 逆前方向平面
	//----------------------------------------
	Plane* getpPlaneInverseForward();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~OBB();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param position 座標
	//! @param length   各辺の長さ
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D length);

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

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
	//! @brief 最小値と最大値算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationMinAndMax() override;

	//----------------------------------------
	//! @brief 平面算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationPlane();
};



#endif