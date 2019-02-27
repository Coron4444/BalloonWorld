//================================================================================
//!	@file	 ResultSceneState_Start.cpp
//!	@brief	 リザルトシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
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
// 関数定義
//****************************************
void ResultSceneState_Start::Init()
{
	// リザルトシーンの取得
	result_scene_ = (ResultScene*)getpScene();

	// クリアロゴ
	ClearLogoFactory clear_logo_factory;
	ClearLogo* temp = clear_logo_factory.Create();
	temp->setScore(result_scene_->getpSceneManager()->getpCommonData()->getScore());

	// プッシュスペースロゴ
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