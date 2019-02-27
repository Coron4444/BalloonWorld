//================================================================================
//!	@file	 TitleScene.cpp
//!	@brief	 タイトルシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../TitleScene.h"



//****************************************
// 関数定義
//****************************************
TitleScene::TitleScene(StateBase* state)
	: SceneNull(state)
{
}



void TitleScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_TITLE);

	// ステート初期化
	SceneNull::Init();
}



void TitleScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_TITLE);

	// ステート終了
	SceneNull::Uninit();
}