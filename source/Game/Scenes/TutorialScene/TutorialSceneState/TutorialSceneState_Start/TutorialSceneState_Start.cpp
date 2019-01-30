//================================================================================
//!	@file	 TutorialSceneState_Start.cpp
//!	@brief	 �`���[�g���A���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialSceneState_Start.h"
#include "../../TutorialScene.h"
#include "../TutorialSceneState_End/TutorialSceneState_End.h"

#include <SceneManager\SceneManager.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <GameObjectManager/GameObjectManager.h>

#include <2D/UI/TutorialLogo/TutorialLogoFactory/TutorialLogoFactory.h>
#include <2D/UI/PushSpaceLogo/PushSpaceLogoFactory/PushSpaceLogoFactory.h>



//****************************************
// �֐���`
//****************************************
void TutorialSceneState_Start::Init()
{
	// �`���[�g���A���V�[���̎擾
	tutorial_scene_ = (TutorialScene*)getpScene();

	// �f�t�H���g�J�����̍쐬
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->getpCamera()->setState(nullptr);

	// �`���[�g���A�����S
	TutorialLogoFactory tutorial_logo_factory;
	tutorial_scene_->setTutorialLogo(tutorial_logo_factory.Create());

	// �v�b�V���X�y�[�X���S
	PushSpaceLogoFactory push_space_logo_factory;
	push_space_logo_factory.Create();
}



void TutorialSceneState_Start::Uninit()
{
}



void TutorialSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		tutorial_scene_->setState(new TutorialSceneState_End());
	}
}



void TutorialSceneState_Start::Reset()
{
}