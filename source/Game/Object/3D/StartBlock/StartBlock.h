//================================================================================
//!	@file	 StartBlock.h
//!	@brief	 スタートブロックClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_START_BLOCK_H_
#define _START_BLOCK_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   スタートブロックClass
//!
//! @details スタートブロックのClass
//************************************************************
class StartBlock : public GameObjectNull
{
//====================
// 定数
//====================
private:
	static const Vec3 SCALE;				//!< 拡縮
	static const float ROTATION_SPEED;		//!< 回転


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vec3 value);

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw      描画基底クラス
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;
};



#endif