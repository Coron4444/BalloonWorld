//================================================================================
//!	@file	 Enemy.h
//!	@brief	 敵Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_ENEMY_H_
#define _ENEMY_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   敵Class
//!
//! @details 敵のClass
//************************************************************
class Enemy : public GameObjectNull
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *update    更新基底クラス
	//! @param *draw      描画基底クラス
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);
};



#endif