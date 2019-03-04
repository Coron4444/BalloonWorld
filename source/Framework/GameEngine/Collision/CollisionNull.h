//================================================================================
//!	@file	 Collision.h
//!	@brief	 空白衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "CollisionBase.h"



//************************************************************														   
//! @brief   空白衝突Class
//!
//! @details 衝突の空白Class
//************************************************************
class CollisionNull : public CollisionBase
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~CollisionNull();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() override;

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset() override;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() override;

	//----------------------------------------
	//! @brief 衝突時関数
	//! @details
	//! @param *information 衝突情報
	//! @retval void なし
	//----------------------------------------
	virtual void HitCollision(CollisionInformation* information) override;

	//----------------------------------------
	//! @brief フィールドとの衝突時関数
	//! @details
	//! @param position_y フィールドの高さ
	//! @retval void なし
	//----------------------------------------
	virtual void HitGround(float position_y) override;
};



#endif