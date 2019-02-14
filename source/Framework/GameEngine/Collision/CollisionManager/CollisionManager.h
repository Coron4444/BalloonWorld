//================================================================================
//!	@file	 CollisionManager.h
//!	@brief	 衝突マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <vector>

#include "LinerOctree.h"
#include "../CollisionObject.h"
#include "../CollisionInformation.h"

#include <Tool/LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class CollisionBase;
class GameObjectBase;
class MeshPlanePolygon;



//************************************************************														   
//! @brief   衝突マネージャーClass
//!
//! @details 登録されている衝突基底クラスを管理するClass
//************************************************************
class CollisionManager
{
//====================
// 定数
//====================
public:
	static const unsigned ARRAY_NUM = 10000;		//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< 全衝突配列
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< 解放待ち配列
	LinerOctree<CollisionObject*>* liner_octree_ = nullptr;			//!< 8分木
	std::vector<CollisionObject*> collision_objects_list_;			//!< 衝突リスト
	MeshPlanePolygon* ground_polygon_;								//!< 地面ポリゴン


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 地面ポリゴン設定関数
	//! @details
	//! @param *ground_polygon 地面ポリゴン
	//! @retval void なし
	//----------------------------------------
	void setGround(MeshPlanePolygon* ground_polygon);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 衝突基底クラスの追加関数
	//! @details
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddCollisionBaseToArray(CollisionBase* collision);

	//----------------------------------------
	//! @brief 衝突基底クラスの上書き関数
	//! @details
	//! @param *game_object   ゲームオブジェクト
	//! @param *new_collision 新規衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayCollisionBase(GameObjectBase* game_object,
									 CollisionBase* new_collision);

	//----------------------------------------
	//! @brief 衝突基底クラスの解放関数
	//! @details
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseCollisionBaseFromArray(CollisionBase* collision);


private:
	//----------------------------------------
	//! @brief 追加待ち配列の中身を追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief 解放待ち配列の中身を解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief 衝突判定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CollisionDetermination();

	//----------------------------------------
	//! @brief 地面との衝突判定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CollisionGround();

	//----------------------------------------
	//! @brief 実際の計算関数
	//! @details
	//! @param *collision_object0 衝突オブジェクト0
	//! @param *collision_object1 衝突オブジェクト1
	//! @retval void なし
	//----------------------------------------
	void ActualCalculation(CollisionObject* collision_object0,
						   CollisionObject* collision_object1);

	//----------------------------------------
	//! @brief 衝突計算振り分け関数
	//! @details
	//! @param *information0     衝突情報0
	//! @param *information1     衝突情報1
	//! @param *collision_shape0 衝突形状0
	//! @param *collision_shape1 衝突形状1
	//! @retval void なし
	//----------------------------------------
	bool SortCollisionCalculation(CollisionInformation* information0,
								  CollisionInformation* information1,
								  CollisionObject::Shape* collision_shape0,
								  CollisionObject::Shape* collision_shape1);

	//----------------------------------------
	//! @brief Debug表示関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DebugDisplay();
};



#endif
