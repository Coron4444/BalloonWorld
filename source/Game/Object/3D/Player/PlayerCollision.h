//================================================================================
//!	@file	 PlayerCollision.h
//!	@brief	 プレイヤー衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================
#ifndef	_PLAYER_COLLISION_H_
#define _PLAYER_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//****************************************
// クラス定義
//****************************************
class Player;



//************************************************************														   
//! @brief   プレイヤー衝突Class
//!
//! @details プレイヤーの衝突Class
//************************************************************
class PlayerCollision : public CollisionNull
{
//====================
// 列挙型定義
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE_SPHERE,
		MAX
	};


//====================
// 定数
//====================
private:
	static const float BOUNDING_SPHERE_RADIUS;		//!< バウンディング球の半径
	static const float SUBSTANCE_SPHERE_RADIUS;		//!< 実体球の半径


//====================
// 変数
//====================
private:
	CollisionObjects* collision_objects_;	//!< 衝突オブジェクト群
	CollisionObject* bounding_sphere_;		//!< バウンディング球
	CollisionObject* substance_sphere_;		//!< 実体球
	Player* player_;						//!< プレイヤー


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
	void Init() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief 衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void HitCollision(CollisionBase* hit_collision,
					  CollisionObject* hit_object,
					  CollisionObject* hit_my_object) override;

	//----------------------------------------
	//! @brief 非衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void NotHitCollision(CollisionBase*	hit_collision,
						 CollisionObject* hit_object,
						 CollisionObject* hit_my_object) override;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	void HitGround(float position_y) override;


private:
	//----------------------------------------
	//! @brief バウンディング球衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void HitBoundingSphere(CollisionBase* hit_collision,
						   CollisionObject* hit_object,
						   CollisionObject* hit_my_object);

	//----------------------------------------
	//! @brief バウンディング球非衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void NotHitBoundingSphere(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object);

	//----------------------------------------
	//! @brief 実体球衝突時関数
	//! @details
	//! @param *hit_collision 相手の衝突基底クラス
	//! @param *hit_object    相手の衝突オブジェクト
	//! @param *hit_my_object 自分の衝突オブジェクト
	//! @retval void なし
	//----------------------------------------
	void HitSubstance(CollisionBase* hit_collision,
					  CollisionObject* hit_object,
					  CollisionObject* hit_my_object);
};



#endif