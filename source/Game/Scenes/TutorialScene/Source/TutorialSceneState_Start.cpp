//================================================================================
//!	@file	 TutorialSceneState_Start.cpp
//!	@brief	 チュートリアルシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
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
// 関数定義
//****************************************
void TutorialSceneState_Start::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)getpScene();

	// チュートリアルロゴ
	TutorialLogoFactory tutorial_logo_factory;
	tutorial_scene_->setTutorialLogo(tutorial_logo_factory.Create());

	// プッシュスペースロゴ
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