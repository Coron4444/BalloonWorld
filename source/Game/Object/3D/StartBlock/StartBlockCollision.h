//================================================================================
//!	@file	 StartBlockCollision.h
//!	@brief	 スタートブロック衝突Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>




//************************************************************														   
//! @brief   スタートブロック衝突Class
//!
//! @details スタートブロックの衝突Class
//************************************************************
class StartBlockCollision : public CollisionNull
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
	static const float BOUNDING_SPHERE_RADIUS;		//!< バウンディング球半径
	static const float SUBSTANCE_SPHERE_RADIUS;		//!< 実体球半径


//====================
// 変数
//====================
private:
	CollisionObjects* collision_objects_;		//!< 衝突オブジェクト群
	CollisionObject* bounding_sphere_;			//!< バウンディング球
	CollisionObject* substance_sphere_;			//!< 実体球


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
};



#endif