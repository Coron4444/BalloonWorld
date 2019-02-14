//================================================================================
//!	@file	 CollisionInformation.h
//!	@brief	 衝突情報Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/14
//================================================================================
#ifndef	_COLLISION_INFORMATION_H_
#define _COLLISION_INFORMATION_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionObject.h"
#include "CollisionShape/LineSegment.h"

#include <Tool/Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class CollisionBase;



//************************************************************														   
//! @brief   衝突情報Class
//!
//! @details 衝突の情報Class
//************************************************************
class CollisionInformation
{
//====================
// 変数
//====================
private:
	Vector3D collision_point_;					//!< 衝突点
	Vector3D collision_normal_;					//!< 衝突点法線
	LineSegment* collision_line_segment_;		//!< 衝突線分(平面用)
	Vector3D nesting_vector_;					//!< めり込みベクトル
	CollisionBase* opponent_base_;				//!< 相手の衝突基底クラス
	CollisionObject* my_object_;				//!< 自分の衝突オブジェクト
	CollisionObject* opponent_object_;			//!< 相手の衝突オブジェクト
	CollisionObject::Shape* my_shape_;			//!< 自分の衝突形状
	CollisionObject::Shape* opponent_shape_;	//!< 相手の衝突形状


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 衝突点取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 衝突点
	//----------------------------------------
	Vector3D* getpCollisionPoint();

	//----------------------------------------
	//! @brief 衝突点設定関数
	//! @details
	//! @param value めり込みベクトル
	//! @retval void なし
	//----------------------------------------
	void setCollisionPoint(Vector3D value);

	//----------------------------------------
	//! @brief 衝突点法線取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 衝突点法線
	//----------------------------------------
	Vector3D* getpCollisionPointNormal();

	//----------------------------------------
	//! @brief 衝突点法線設定関数
	//! @details
	//! @param value 衝突点法線
	//! @retval void なし
	//----------------------------------------
	void setCollisionPointNormal(Vector3D value);

	//----------------------------------------
	//! @brief  衝突線分(平面用)取得関数
	//! @details
	//! @param void なし
	//! @retval LineSegment*  衝突線分(平面用)
	//----------------------------------------
	LineSegment* getpCollisionLineSegment();

	//----------------------------------------
	//! @brief  衝突線分(平面用)設定関数
	//! @details
	//! @param *value  衝突線分(平面用)
	//! @retval void なし
	//----------------------------------------
	void setCollisionLineSegment(LineSegment* value);

	//----------------------------------------
	//! @brief めり込みベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* めり込みベクトル
	//----------------------------------------
	Vector3D* getpNestingVector();

	//----------------------------------------
	//! @brief めり込みベクトル設定関数
	//! @details
	//! @param value めり込みベクトル
	//! @retval void なし
	//----------------------------------------
	void setNestingVector(Vector3D value);

	//----------------------------------------
	//! @brief 相手の衝突基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionBase* 相手の衝突基底クラス
	//----------------------------------------
	CollisionBase* getpOpponentCollisionBase();

	//----------------------------------------
	//! @brief 相手の衝突基底クラス設定関数
	//! @details
	//! @param *value 相手の衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setOpponentCollisionBase(CollisionBase* value);

	//----------------------------------------
	//! @brief 自分の衝突オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionObject* 自分の衝突オブジェクト
	//----------------------------------------
	CollisionObject* getpMyObject();

	//----------------------------------------
	//! @brief 自分の衝突オブジェクト設定関数
	//! @details
	//! @param *value 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setMyObject(CollisionObject* value);

	//----------------------------------------
	//! @brief 相手の衝突オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionObject* 相手の衝突オブジェクト
	//----------------------------------------
	CollisionObject* getpOpponentObject();

	//----------------------------------------
	//! @brief 相手の衝突オブジェクト設定関数
	//! @details
	//! @param *value 相手の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setOpponentObject(CollisionObject* value);

	//----------------------------------------
	//! @brief 自分の衝突形状取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionObject::Shape* 自分の衝突形状
	//----------------------------------------
	CollisionObject::Shape* getpMyShape();

	//----------------------------------------
	//! @brief 自分の衝突形状設定関数
	//! @details
	//! @param *value 自分の衝突形状
	//! @retval void なし
	//----------------------------------------
	void setMyShape(CollisionObject::Shape* value);

	//----------------------------------------
	//! @brief 相手の衝突形状取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionObject::Shape* 相手の衝突形状
	//----------------------------------------
	CollisionObject::Shape* getpOpponentShape();

	//----------------------------------------
	//! @brief 相手の衝突形状設定関数
	//! @details
	//! @param *value 相手の衝突形状
	//! @retval void なし
	//----------------------------------------
	void setOpponentShape(CollisionObject::Shape* value);
};



#endif