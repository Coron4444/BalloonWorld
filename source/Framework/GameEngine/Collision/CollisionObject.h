//================================================================================
//!	@file	 CollisionObject.h
//!	@brief	 衝突オブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/14
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
#include "CollisionManager/ObjectOfTree.h"



//****************************************
// クラス宣言
//****************************************
class CollisionBase;



//************************************************************														   
//! @brief   衝突オブジェクトClass
//!
//! @details 衝突オブジェクトのClass
//************************************************************
class CollisionObject
{
//====================
// クラス定義
//====================
public:
	//****************************************											   
	//! @brief   衝突形状Class
	//!
	//! @details 衝突の形状Class
	//****************************************
	class Shape
	{
	//====================
	// 定数
	//====================
	private:
		static const int TAG_NONE;		//!< タグなし時の値


	//====================
	// 変数
	//====================
	private:
		int	tag_ = TAG_NONE;		//!< タグ
		CollisionShapeBase* shape_;	//!< 形状


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
		CollisionShapeBase* getpShape();

		//----------------------------------------
		//! @brief 衝突形状取得関数
		//! @details
		//! @param value 衝突形状
		//! @retval void なし
		//----------------------------------------
		void setShape(CollisionShapeBase* value);


	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief 初期化関数
		//! @details
		//! @param tag    タグ
		//! @param *shape 衝突形状
		//! @retval void なし
		//----------------------------------------
		void Init(int tag, CollisionShapeBase* shape);

		//----------------------------------------
		//! @brief 終了関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		void Uninit();
	};


//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 10000;	//!< 配列数
	static const int TAG_NONE;					//!< タグなし時の値


//====================
// 変数
//====================
private:
	int	tag_ = TAG_NONE;								//!< タグ
	LimitedPointerArray<Shape*, ARRAY_NUM> all_shape_;	//!< 全衝突形状配列
	CollisionBase* collision_base_ = nullptr;			//!< 衝突基底クラス
	ObjectOfTree<CollisionObject*>* object_of_tree_;	//!< 分木オブジェクト
	AABB octree_aabb_;									//!< 8分木用AABB
	

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
	//! @brief 配列の終端インデックス取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned 配列の終端インデックス
	//----------------------------------------
	unsigned getEndIndexOfArray();

	//----------------------------------------
	//! @brief 衝突形状取得関数
	//! @details
	//! @param index インデックス
	//! @retval Shape* 衝突形状
	//----------------------------------------
	Shape* getpShape(unsigned index);

	//----------------------------------------
	//! @brief 衝突基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionBase* 衝突基底クラス
	//----------------------------------------
	CollisionBase* getpCollisionBase();

	//----------------------------------------
	//! @brief 衝突基底クラス設定関数
	//! @details
	//! @param *value 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setCollisionBase(CollisionBase* value);

	//----------------------------------------
	//! @brief 分木オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval ObjectOfTree<CollisionObject*>* 分木オブジェクト
	//----------------------------------------
	ObjectOfTree<CollisionObject*>* getpObjectOfTree();

	//----------------------------------------
	//! @brief 分木オブジェクト設定関数
	//! @details
	//! @param value 分木オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setObjectOfTree(ObjectOfTree<CollisionObject*>* value);

	//----------------------------------------
	//! @brief 8分木用AABBポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval AABB* 8分木用AABBポインタ
	//----------------------------------------
	AABB* getOctreeAABB();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化
	//! @details
	//! @param tag        タグ
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(int tag, CollisionBase* collision);

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 衝突形状追加関数
	//! @details
	//! @param tag   タグ
	//! @param shape 形状
	//! @retval void なし
	//----------------------------------------
	void AddShape(int tag, CollisionShapeBase* shape);

	//----------------------------------------
	//! @brief 衝突形状解放関数
	//! @details
	//! @param tag   タグ
	//! @retval void なし
	//----------------------------------------
	void ReleaseShape(int tag);

	//----------------------------------------
	//! @brief 衝突オブジェクト全解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseAllShape();

private:
	//----------------------------------------
	//! @brief AABB更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAABB();
};



#endif
