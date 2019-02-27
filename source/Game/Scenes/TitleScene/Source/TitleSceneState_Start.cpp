//================================================================================
//!	@file	 TitleSceneState_Start.cpp
//!	@brief	 �^�C�g���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TitleSceneState_Start.h"
#include "../TitleScene.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>

#include <Object/2D/TitleLogo/TitleLogoFactory.h>
#include <Object/2D/PushSpaceLogo/PushSpaceLogoFactory.h>
#include <Object/3D/SkyDome/SkyDomeFactory.h>

#include <Scenes/TutorialScene/TutorialScene.h>
#include <Scenes/TutorialScene/TutorialSceneState_Start.h>



//****************************************
// �֐���`
//****************************************
void TitleSceneState_Start::Init()
{
	// �^�C�g���V�[���̎擾
	title_scene_ = (TitleScene*)getpScene();

	// �^�C�g�����S
	TitleLogoFactory title_logo_factory;
	title_logo_factory.Create();

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();

	// �X�J�C�h�[��
	SkyDomeFactory sky_dome_factory;
	sky_dome_factory.Create();
}



void TitleSceneState_Start::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()->getTrigger(0, XINPUT_GAMEPAD_X))
	{
		SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_KETEI);
		title_scene_->getpSceneManager()
			->setNextScene(new TutorialScene(new TutorialSceneState_Start()));
	}
}