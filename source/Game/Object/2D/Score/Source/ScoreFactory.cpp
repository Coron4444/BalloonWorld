//================================================================================
//!	@file	 ScoreFactory.cpp
//!	@brief	 �X�R�A����Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ScoreFactory.h"
#include "../Score.h"
#include "../ScoreDraw.h"



//****************************************
// �֐���`
//****************************************
Score* ScoreFactory::Create(GameScene* game_scene)
{
	Score* temp = new Score();
	temp->Init(new ScoreDraw(),
			   game_scene);
	return temp;
}