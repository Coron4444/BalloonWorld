//================================================================================
//!	@file	 AABB.h
//!	@brief	 AABBClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_AABB_H_
#define _AABB_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShapeBase.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   AABBClass
//!
//! @details AABBのClass
//************************************************************
class AABB : public CollisionShapeBase
{
//====================
// 変数
//====================
private:
	Vector3D position_;	//!< 座標
	Vector3D length_;	//!< 各辺の長さ
	Vector3D min_;		//!< 最小値
	Vector3D max_;		//!< 最大値


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
	//! @brief 各辺の長さ取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 各辺の長さ
	//----------------------------------------
	Vector3D* getpLength();

	//----------------------------------------
	//! @brief 各辺の長さ設定関数
	//! @details
	//! @param value 各辺の長さ
	//! @retval void なし
	//----------------------------------------
	void setLength(Vector3D value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~AABB();

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
	//! @details
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