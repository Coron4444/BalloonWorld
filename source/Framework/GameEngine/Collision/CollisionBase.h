//================================================================================
//!	@file	 CollisionBase.h
//!	@brief	 衝突BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../ComponentBase.h"
#include "CollisionObject.h"
#include "CollisionManager/CollisionCalculation.h"
#include "CollisionInformation.h"

#include <Tool/LimitedPointerArray.h>
#include <Tool/Transform.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   衝突BaseClass
//!
//! @details 衝突のBaseClass
//************************************************************
class CollisionBase : public ComponentBase
{
//====================
// 列挙型定義
//====================
public:
	// タイプ
	enum class Type
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		GOAL,
		MAX
	};


//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//====================
// 変数
//====================
private:
	Type type_ = Type::NONE;			//!< タイプ
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< 衝突オブジェクト配列
	bool is_judgment_ground_ = true;	//!< 地面との判定フラグ


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
	//! @brief 配列の最後の末尾のインデックス取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned 配列の最後の末尾のインデックス
	//----------------------------------------
	unsigned getEndIndexOfArray();

	//----------------------------------------
	//! @brief 衝突オブジェクト取得関数
	//! @details
	//! @param index インデックス
	//! @retval CollisionObject* 衝突オブジェクト
	//----------------------------------------
	CollisionObject* getpCollisionObject(unsigned index);

	//----------------------------------------
	//! @brief 地面との判定フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 地面との判定フラグ
	//----------------------------------------
	bool getIsJudgmentGround();

	//----------------------------------------
	//! @brief 地面との判定フラグ設定関数
	//! @details
	//! @param value 地面との判定フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsJudgmentGround(bool value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionBase() = 0;

	//----------------------------------------
	//! @brief 衝突時関数
	//! @details
	//! @param *information 衝突情報
	//! @retval void なし
	//----------------------------------------
	virtual void HitCollision(CollisionInformation* information) = 0;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief 衝突オブジェクト追加関数
	//! @details
	//! @param *object 衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddCollisionObject(CollisionObject* object);

	//----------------------------------------
	//! @brief 衝突オブジェクト上書き関数
	//! @details
	//! @param *old_object 古い衝突オブジェクト
	//! @param *new_object 新しい衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void OverwriteCollisionsObject(CollisionObject* old_object,
								   CollisionObject* new_object);

	//----------------------------------------
	//! @brief 衝突オブジェクト解放関数
	//! @details
	//! @param *object 衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void ReleaseCollisionObject(CollisionObject* object);

	//----------------------------------------
	//! @brief 衝突オブジェクト全解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseAllCollisionObject();

	//----------------------------------------
	//! @brief 衝突オブジェクト全更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAllCollisionObject();
};



#endif