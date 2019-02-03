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
#include <GameEngine/Input/InputManager/InputManager.h>
#include <Tool/SafeRelease.h>

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

	if (result_scene_->getpSceneManager()->getpCommonData()->getIsClear())
	{
		// �N���A���S
		ClearLogoFactory clear_logo_factory;
		clear_logo_factory.Create();
	}
	else
	{
		// ���s���S
		FailureLogoFactory failure_logo_factory;
		failure_logo_factory.Create();
	}

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void ResultSceneState_Start::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE))
	{
		result_scene_->getpSceneManager()
			->setNextScene(new TitleScene(new TitleSceneState_Start()));
	}
}