//================================================================================
//!	@file	 ClearLogo.h
//!	@brief	 クリアロゴClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_CLEAR_LOGO_H_
#define _CLEAR_LOGO_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   クリアロゴClass
//!
//! @details クリアロゴのClass
//************************************************************
class ClearLogo : public GameObjectNull
{
private:
	int score_ = 0;

public:
	int getScore();
	void setScore(int value);

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
};



#endif