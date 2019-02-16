//================================================================================
//!	@file	 EnemyCollision.h
//!	@brief	 敵衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_ENEMY_COLLISION_H_
#define _ENEMY_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//************************************************************														   
//! @brief   敵衝突Class
//!
//! @details 敵の衝突Class
//************************************************************
class EnemyCollision : public CollisionNull
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
	static const Vec3 MAIN_OBB_LENGTH;		//!< メインOBB長さ


//====================
// 変数
//====================
private:
	CollisionObject* collision_object_;		//!< 衝突オブジェクト
	OBB* main_obb_;							//!< メインOBB


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