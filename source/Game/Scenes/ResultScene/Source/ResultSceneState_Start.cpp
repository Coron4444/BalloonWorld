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
#include <GameEngine/Input/InputManager/InputManager.h>
#include <Tool/SafeRelease.h>

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

	if (result_scene_->getpSceneManager()->getpCommonData()->getIsClear())
	{
		// クリアロゴ
		ClearLogoFactory clear_logo_factory;
		clear_logo_factory.Create();
	}
	else
	{
		// 失敗ロゴ
		FailureLogoFactory failure_logo_factory;
		failure_logo_factory.Create();
	}

	// プッシュスペースロゴ
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