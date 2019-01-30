//================================================================================
//!	@file	 Score.cpp
//!	@brief	 スコアClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_SCORE_H_
#define _SCORE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Numbers\Numbers.h>
#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   スコアClass
//!
//! @details スコアのClass
//************************************************************
class Score : public GameObjectNull
{
//====================
// 変数
//====================
private:
	GameScene* game_scene_;		//!< ゲームシーン


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ゲームシーン取得関数
	//! @details
	//! @param void なし
	//! @retval GameScene* ゲームシーン
	//----------------------------------------
	GameScene* getpGameScene();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw       描画基底クラス
	//! @param *game_scene ゲームシーン
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw,
			  GameScene* game_scene);
};



#endif