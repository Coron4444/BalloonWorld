//================================================================================
//!	@file	 TutorialSceneState_End.cpp
//!	@brief	 チュートリアルシーンステート(エンド)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../TutorialSceneState_End.h"
#include "../TutorialScene.h"

#include <GameEngine/Scene/SceneManager/SceneManager.h>

#include <Object/2D/TutorialLogo/TutorialLogoFactory.h>

#include <Scenes/GameScene/GameScene.h>
#include <Scenes/GameScene/GameSceneState_Start.h>




//****************************************
// 関数定義
//****************************************
void TutorialSceneState_End::Init()
{
	// チュートリアルシーンの取得
	tutorial_scene_ = (TutorialScene*)getpScene();

	tutorial_scene_->getpTutorialLogo()->setLogoNum(1);
}



void TutorialSceneState_End::Update()
{
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()->getTrigger(0, XINPUT_GAMEPAD_X))
	{
		SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_KETEI);
		tutorial_scene_->getpSceneManager()
			->setNextScene(new GameScene(new GameSceneState_Start()));
	}
}