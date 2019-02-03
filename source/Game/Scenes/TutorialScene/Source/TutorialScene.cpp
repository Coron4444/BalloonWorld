//================================================================================
//!	@file	 TutorialScene.cpp
//!	@brief	 �`���[�g���A���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TutorialScene.h"



//****************************************
// �v���p�e�B��`
//****************************************
TutorialLogo* TutorialScene::getpTutorialLogo()
{ 
	return tutorial_logo_; 
}

void TutorialScene::setTutorialLogo(TutorialLogo* value)
{ 
	tutorial_logo_ = value; 
}



//****************************************
// �֐���`
//****************************************
TutorialScene::TutorialScene(StateBase* state)
	: SceneBase(state)
{
}