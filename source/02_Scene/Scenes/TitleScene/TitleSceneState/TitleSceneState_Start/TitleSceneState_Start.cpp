//================================================================================
//!	@file	 TitleSceneState_Start.cpp
//!	@brief	 �^�C�g���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TitleSceneState_Start.h"
#include "../../TitleScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TutorialScene/TutorialScene.h>
#include <Scenes/TutorialScene/TutorialSceneState/TutorialSceneState_Start/TutorialSceneState_Start.h>

#include <GameObjectManager/GameObjectManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame/MeterToFrame/MeterToFrame.h>
#include <Keyboard/Keyboard.h>

#include <2D/UI/TitleLogo/TitleLogoFactory/TitleLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



//****************************************
// �֐���`
//****************************************
void TitleSceneState_Start::Init()
{
	// �^�C�g���V�[���̎擾
	title_scene_ = (TitleScene*)getpScene();

	// �f�t�H���g�J�����̍쐬
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->getpCamera()->setState(nullptr);

	// �^�C�g�����S
	TitleLogoFactory title_logo_factory;
	title_logo_factory.Create();

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void TitleSceneState_Start::Uninit()
{
}



void TitleSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		title_scene_->getpSceneManager()
			->setNextScene(new TutorialScene(new TutorialSceneState_Start()));
	}
}



void TitleSceneState_Start::Reset()
{

}