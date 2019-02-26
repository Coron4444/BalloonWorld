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
		MAIN,
		MAX
	};

	enum class ShapeTag
	{
		NONE = -1,
		MAIN,
		TEST,
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
	Player* player_;						//!< プレイヤー
	Vector3D normal_;

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
	//! @param *information 衝突情報
	//! @retval void なし
	//----------------------------------------
	void HitCollision(CollisionInformation* information) override;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	void HitGround(float position_y) override;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	//void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief メイン球衝突時関数
	//! @details
	//! @param *information 衝突情報
	//! @retval void なし
	//----------------------------------------
	void HitMainSphere(CollisionInformation* information);
};



#endif