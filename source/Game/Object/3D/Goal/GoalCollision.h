//================================================================================
//!	@file	 GoalCollision.h
//!	@brief	 ゴール衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================
#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>




//************************************************************														   
//! @brief   ゴール衝突Class
//!
//! @details ゴールの衝突Class
//************************************************************
class GoalCollision : public CollisionNull
{
//====================
// 列挙型定義
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		MAIN,
		MAX
	};

	enum class ShapeTag
	{
		NONE = -1,
		MAIN,
		MAX
	};


//====================
// 定数
//====================
private:
	static const float MAIN_SPHERE_RADIUS;		//!< メイン球半径


//====================
// 変数
//====================
private:
	CollisionObject* collision_object_;		//!< 衝突オブジェクト
	Sphere* main_sphere_;					//!< メイン球


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