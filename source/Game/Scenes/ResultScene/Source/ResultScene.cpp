//================================================================================
//!	@file	 ResultScene.cpp
//!	@brief	 リザルトシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ResultScene.h"

#include <Resource/Sound/SoundManager.h>



//****************************************
// 関数定義
//****************************************
ResultScene::ResultScene(StateBase* state)
	: SceneNull(state)
{
}



void ResultScene::Init()
{
	SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::BGM_RESULT);

	// ステート初期化
	SceneNull::Init();
}



void ResultScene::Uninit()
{
	SoundManager::getpInstance()->Stop(SoundManager::Type::BGM_RESULT);

	// ステート終了
	SceneNull::Uninit();
}