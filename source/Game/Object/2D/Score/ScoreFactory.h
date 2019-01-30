//================================================================================
//!	@file	 ScoreFactory.h
//!	@brief	 スコア生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_SCORE_FACTORY_H_
#define _SCORE_FACTORY_H_



//****************************************
// クラス宣言
//****************************************
class Score;
class GameScene;



//************************************************************														   
//! @brief   スコア生成Class
//!
//! @details スコアの生成Class
//************************************************************
class ScoreFactory
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief スコア生成関数
	//! @details
	//! @param *game_scene ゲームシーン
	//! @retval Score* スコア
	//----------------------------------------
	Score* Create(GameScene* game_scene);
};



#endif