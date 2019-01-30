//================================================================================
//!	@file	 ScoreFactory.cpp
//!	@brief	 スコア生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ScoreFactory.h"
#include "../Score.h"
#include "../ScoreDraw.h"



//****************************************
// 関数定義
//****************************************
Score* ScoreFactory::Create(GameScene* game_scene)
{
	Score* temp = new Score();
	temp->Init(new ScoreDraw(),
			   game_scene);
	return temp;
}