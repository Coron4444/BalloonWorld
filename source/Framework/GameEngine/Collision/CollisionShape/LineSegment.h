//================================================================================
//!	@file	 LineSegment.h
//!	@brief	 線分Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SEGMENT_H_
#define _SEGMENT_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   線分Class
//!
//! @details 線分のClass
//************************************************************
class LineSegment : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;		//!< 座標
	Vector3D vector_;		//!< 方向


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
	//! @brief 方向取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 方向
	//----------------------------------------
	Vector3D* getpVector();

	//----------------------------------------
	//! @brief 方向ベクトル加算済み座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 方向ベクトル加算済み座標
	//----------------------------------------
	Vector3D getAddVectorToPosition();

	//----------------------------------------
	//! @brief 2D線分の傾き取得関数
	//! @details
	//! @param void なし
	//! @retval float 2D線分の傾き
	//----------------------------------------
	float getSlopeOf2DLineSegment();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~LineSegment();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param position 座標
	//! @param vector   方向
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector);

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

private:
	//----------------------------------------
	//! @brief 最小値と最大値算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculationMinAndMax() override;
};



#endif