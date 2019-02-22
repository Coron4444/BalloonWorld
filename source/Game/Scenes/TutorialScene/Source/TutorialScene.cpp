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

#include <Resource/Sound/SoundManager.h>



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
	: SceneNull(state)
{
}



void TutorialScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_TUTORIAL);

	// �X�e�[�g������
	SceneNull::Init();
}



void TutorialScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_TUTORIAL);

	// �X�e�[�g�I��
	SceneNull::Uninit();
}