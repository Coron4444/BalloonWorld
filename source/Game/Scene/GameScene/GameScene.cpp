//================================================================================
//!	@file	 GameScene.cpp
//!	@brief	 �Q�[���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GameScene.h"



//****************************************
// �v���p�e�B��`
//****************************************
bool GameScene::getIsClear() 
{ 
	return is_clear_; 
}



void GameScene::setIsClear(bool value) 
{ 
	is_clear_ = value; 
}



int GameScene::getScore() 
{ 
	return score_; 
}



void GameScene::setScore(int value) 
{ 
	score_ = value; 
}



int GameScene::getGameOver() 
{ 
	return game_over_; 
}



void GameScene::setGameOver(int value) 
{
	game_over_ = value; 
}



//****************************************
// �֐���`
//****************************************
GameScene::GameScene(StateBase* state)
	: SceneBase(state) 
{
}