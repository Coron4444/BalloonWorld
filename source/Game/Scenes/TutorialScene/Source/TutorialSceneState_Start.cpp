//================================================================================
//!	@file	 TutorialSceneState_Start.cpp
//!	@brief	 �`���[�g���A���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TutorialSceneState_Start.h"
#include "../TutorialScene.h"
#include "../TutorialSceneState_End.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <GameEngine/Input/InputManager/InputManager.h>
#include <Resource/Sound/SoundManager.h>

#include <Object/2D/TutorialLogo/TutorialLogoFactory.h>
#include <Object/2D/PushSpaceLogo/PushSpaceLogoFactory.h>



//****************************************
// �֐���`
//****************************************
void TutorialSceneState_Start::Init()
{
	// �`���[�g���A���V�[���̎擾
	tutorial_scene_ = (TutorialScene*)getpScene();

	// �`���[�g���A�����S
	TutorialLogoFactory tutorial_logo_factory;
	tutorial_scene_->setTutorialLogo(tutorial_logo_factory.Create());

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void TutorialSceneState_Start::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()->getTrigger(0, XINPUT_GAMEPAD_X))
	{
		SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_KETEI);
		tutorial_scene_->setState(new TutorialSceneState_End());
	}
}