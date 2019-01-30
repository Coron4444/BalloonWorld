//================================================================================
//!	@file	 Score.cpp
//!	@brief	 �X�R�AClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_SCORE_H_
#define _SCORE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Numbers\Numbers.h>
#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   �X�R�AClass
//!
//! @details �X�R�A��Class
//************************************************************
class Score : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	GameScene* game_scene_;		//!< �Q�[���V�[��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Q�[���V�[���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval GameScene* �Q�[���V�[��
	//----------------------------------------
	GameScene* getpGameScene();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw       �`����N���X
	//! @param *game_scene �Q�[���V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw,
			  GameScene* game_scene);
};



#endif