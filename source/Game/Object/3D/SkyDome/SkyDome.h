//================================================================================
//!	@file	 SkyDome.h
//!	@brief	 天球Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================
#ifndef	_SKY_DOME_H_
#define _SKY_DOME_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   天球Class
//!
//! @details 天球のClass
//************************************************************
class SkyDome : public GameObjectNull
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw);

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;
};



#endif