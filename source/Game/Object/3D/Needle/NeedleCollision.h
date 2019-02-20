//================================================================================
//!	@file	 NeedleCollision.h
//!	@brief	 棘衝突Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_NEEDLE_COLLISION_H_
#define _NEEDLE_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//************************************************************														   
//! @brief   棘衝突Class
//!
//! @details 棘の衝突Class
//************************************************************
class NeedleCollision : public CollisionNull
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