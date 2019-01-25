//================================================================================
//!	@file	 ResultSceneState_Start.cpp
//!	@brief	 ���U���g�V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ResultSceneState_Start.h"
#include "../../ResultScene.h"

#include <SceneManager/SceneManager.h>
#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>

#include <GameObjectManager/GameObjectManager.h>
#include <SafeRelease/SafeRelease.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <Keyboard\Keyboard.h>

#include <2D/UI/ClearLogo/ClearLogoFactory/ClearLogoFactory.h>
#include <2D/UI/FailureLogo/FailureLogoFactory/FailureLogoFactory.h>
#include <2D\UI\PushSpaceLogo\PushSpaceLogoFactory\PushSpaceLogoFactory.h>



//****************************************
// �֐���`
//****************************************
void ResultSceneState_Start::Init()
{
	// ���U���g�V�[���̎擾
	result_scene_ = (ResultScene*)getpScene();

	// �f�t�H���g�J�����̍쐬
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->getpCamera()->setState(nullptr);

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



void ResultSceneState_Start::Uninit()
{
}



void ResultSceneState_Start::Update()
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		result_scene_->getpSceneManager()
			->setNextScene(new TitleScene(new TitleSceneState_Start()));
	}
}



void ResultSceneState_Start::Reset()
{

}