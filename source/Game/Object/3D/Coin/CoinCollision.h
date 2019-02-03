//================================================================================
//!	@file	 CoinCollision.h
//!	@brief	 コイン衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_COLLISION_H_
#define _COIN_COLLISION_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//************************************************************														   
//! @brief   コイン衝突Class
//!
//! @details コインの衝突Class
//************************************************************
class CoinCollision : public CollisionNull
{
//====================
// 列挙型定義
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		BOUNDING_OBB,
		SUBSTANCE_OBB,
		MAX
	};

//====================
// 定数
//====================
private:
	static const Vec3 BOUNDING_OBB_LENGTH;		//!< バウンディングOBB長さ
	static const Vec3 SUBSTANCE_OBB_LENGTH;		//!< 実体OBB長さ


//====================
// 変数
//====================
private:
	CollisionObjects* collision_objects_;		//!< 衝突オブジェクト群
	CollisionObject* bounding_obb_;				//!< バウンディングOBB
	CollisionObject* substance_obb_;			//!< 実体OBB


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