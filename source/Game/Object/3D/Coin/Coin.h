//================================================================================
//!	@file	 Coin.h
//!	@brief	 コインClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_H_
#define _COIN_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   コインClass
//!
//! @details コインのClass
//************************************************************
class Coin : public GameObjectNull
{
//====================
// 変数
//====================
private:
	int color_change_counter_ = 0;					//!< 色変更カウンタ
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};		//!< 色
	bool is_color_change_ = false;					//!< 色変更フラグ

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 色変更カウンタ取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	int* getpColorChangeCounter();

	//----------------------------------------
	//! @brief 色取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	XColor4* getpColor();

	//----------------------------------------
	//! @brief 色変更フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 色変更フラグ
	//----------------------------------------
	bool* getpIsColorChange();

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

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset() override;
};



#endif