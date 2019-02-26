//================================================================================
//!	@file	 Triangle.h
//!	@brief	 三角形平面Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_TRIANGLE_H_
#define _TRIANGLE_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase.h"
#include "Plane.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   三角形平面Class
//!
//! @details 三角形平面のClass
//************************************************************
class Triangle : public CollisionShapeBase
{
//====================
// 定数
//====================
private:	
	static const int MAX_POINT_NUM = 3;		//!< 最大点数


//====================
// 変数
//====================
private:
	Vector3D point_[MAX_POINT_NUM];		//!< 点0
	Plane plane_;						//!< 平面


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 点取得関数
	//! @details
	//! @param index インデックス
	//! @retval Vector3D* 点
	//----------------------------------------
	Vector3D* getpPoint(unsigned index);

	//----------------------------------------
	//! @brief 平面取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 平面
	//----------------------------------------
	Plane* getpPlane();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~Triangle();
	
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param point0 点0
	//! @param point1 点1
	//! @param point2 点2
	//! @retval void なし
	//----------------------------------------
	void Init(Vector3D point0, Vector3D point1, Vector3D point2);

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