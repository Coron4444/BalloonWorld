//================================================================================
//!	@file	 ResultScene.cpp
//!	@brief	 ���U���g�V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ResultScene.h"

#include <Resource/Sound/SoundManager.h>



//****************************************
// �֐���`
//****************************************
ResultScene::ResultScene(StateBase* state)
	: SceneNull(state)
{
}



void ResultScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_RESULT);

	// �X�e�[�g������
	SceneNull::Init();
}



void ResultScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_RESULT);

	// �X�e�[�g�I��
	SceneNull::Uninit();
}