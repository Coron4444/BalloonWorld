//================================================================================
//!	@file	 TitleScene.cpp
//!	@brief	 �^�C�g���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TitleScene.h"



//****************************************
// �֐���`
//****************************************
TitleScene::TitleScene(StateBase* state)
	: SceneNull(state)
{
}



void TitleScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_TITLE);

	// �X�e�[�g������
	SceneNull::Init();
}



void TitleScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_TITLE);

	// �X�e�[�g�I��
	SceneNull::Uninit();
}