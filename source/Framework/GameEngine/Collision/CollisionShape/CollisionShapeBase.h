//================================================================================
//!	@file	 CollisionShapeBase.h
//!	@brief	 衝突形状BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   衝突形状BaseClass
//!
//! @details 衝突形状のBaseClass
//************************************************************
class CollisionShapeBase
{
//====================
// 列挙型定義
//====================
public:
	// 形状タイプ
	enum class Type
	{
		NONE = -1,
		AABB,
		CAPSULE,
		CYLINDER,
		OBB,
		PLANE,
		LINE_SEGMENT,
		SPHERE,
		TRIANGLE,
		MAX
	};


//====================
// 変数
//====================
private:
	Type type_ = Type::NONE;	//!< タイプ
	Vector3D min_;				//!< 最小値
	Vector3D max_;				//!< 最大値

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type タイプ
	//----------------------------------------
	Type getType();

	//----------------------------------------
	//! @brief タイプ設定関数
	//! @details
	//! @param value タイプ
	//! @retval void なし
	//----------------------------------------
	void setType(Type value);
	
	//----------------------------------------
	//! @brief 最大座標取得関数
	//! @details 形状を包むAABBの最大座標
	//! @param void なし
	//! @retval Vector3D* 最大座標
	//----------------------------------------
	Vector3D* getpMax();

	//----------------------------------------
	//! @brief 最小座標取得関数
	//! @details 形状を包むAABBの最小座標
	//! @param void なし
	//! @retval Vector3D* 最小座標
	//----------------------------------------
	Vector3D* getpMin();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionShapeBase() = 0;

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() = 0;

protected:
	//----------------------------------------
	//! @brief 最小値と最大値算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void CalculationMinAndMax() = 0;
};



#endif