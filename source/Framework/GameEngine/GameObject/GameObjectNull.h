//================================================================================
//!	@file	 GameObjectNull.h
//!	@brief	 ゲームオブジェクト空白Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/30
//================================================================================
#ifndef	_GAME_OBJECT_NULL_H_
#define _GAME_OBJECT_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "GameObjectBase.h"



//************************************************************														   
//! @brief   ゲームオブジェクト空白Class
//!
//! @details ゲームオブジェクトの空白Class
//************************************************************
class GameObjectNull : public GameObjectBase
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param is_registration 登録フラグ
	//----------------------------------------
	GameObjectNull(bool is_registration = true);

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~GameObjectNull();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset() override;
};



#endif
