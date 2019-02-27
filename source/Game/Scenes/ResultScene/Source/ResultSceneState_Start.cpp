//================================================================================
//!	@file	 ResultSceneState_Start.cpp
//!	@brief	 ���U���g�V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ResultSceneState_Start.h"
#include "../ResultScene.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>

#include <Object/2D/ClearLogo/ClearLogoFactory.h>
#include <Object/2D/FailureLogo/FailureLogoFactory.h>
#include <Object/2D/PushSpaceLogo/PushSpaceLogoFactory.h>

#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState_Start.h>



//****************************************
// �֐���`
//****************************************
void ResultSceneState_Start::Init()
{
	// ���U���g�V�[���̎擾
	result_scene_ = (ResultScene*)getpScene();

	// �N���A���S
	ClearLogoFactory clear_logo_factory;
	ClearLogo* temp = clear_logo_factory.Create();
	temp->setScore(result_scene_->getpSceneManager()->getpCommonData()->getScore());

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void ResultSceneState_Start::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()->getTrigger(0, XINPUT_GAMEPAD_X))
	{
		SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_KETEI);
		result_scene_->getpSceneManager()
			->setNextScene(new TitleScene(new TitleSceneState_Start()));
	}
}