//================================================================================
//!	@file	 BulletPhysicsManager.h
//!	@brief	 バレットフィジックスオブジェクトClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================
#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionShape/AABB.h"
#include "CollisionShape/Capsule.h"
#include "CollisionShape/Cylinder.h"
#include "CollisionShape/OBB.h"
#include "CollisionShape/Plane.h"
#include "CollisionShape/LineSegment.h"
#include "CollisionShape/Sphere.h"
#include "CollisionShape/Triangle.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   衝突オブジェクトClass
//!
//! @details 衝突オブジェクトのClass
//************************************************************
class CollisionObject
{
//====================
// 定数
//====================
private:
	static const int TAG_NONE = -1;			//!< タグなし時の値


//====================
// 変数
//====================
private:

	CollisionShapeBase* collision_shape_;		//!< 形状
	Vector3D hit_vector_;						//!< めり込みベクトル
	int	tag_;					//!< タグ
	bool is_judgment_ = true;	//!< 判定するかフラグ
	bool is_trigger_ = true;	//!< 物理演算をするかのフラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief タグ取得関数
	//! @details
	//! @param void なし
	//! @retval int タグ
	//----------------------------------------
	int	getTag();

	//----------------------------------------
	//! @brief 衝突形状取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionShapeBase* 衝突形状
	//----------------------------------------
	CollisionShapeBase* getpCollisionShape();

	//----------------------------------------
	//! @brief めり込みベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* めり込みベクトル
	//----------------------------------------
	Vector3D* getpHitVector();

	//----------------------------------------
	//! @brief めり込みベクトル設定関数
	//! @details
	//! @param value めり込みベクトル
	//! @retval void なし
	//----------------------------------------
	void setHitVector(Vector3D value);

	//----------------------------------------
	//! @brief 判定するかフラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 判定するかフラグ
	//----------------------------------------
	bool getIsJudgment();

	//----------------------------------------
	//! @brief 判定するかフラグ設定関数
	//! @details
	//! @param value 判定するかフラグ
	//! @retval void なし
	//----------------------------------------
	void setIsJudgment(bool value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param *collision_shape 衝突形状
	//! @param collision_shape  タグ
	//----------------------------------------
	CollisionObject(CollisionShapeBase* collision_shape, int tag);

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~CollisionObject();

	//----------------------------------------
	//! @brief 衝突用データリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetHitData();
};



#endif
