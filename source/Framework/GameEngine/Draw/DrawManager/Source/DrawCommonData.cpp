//================================================================================
//!	@file	 DrawCommonData.cpp
//!	@brief	 描画共通データClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../DrawCommonData.h"
#include "../../../GameEngine.h"


//****************************************
// プロパティ定義
//****************************************
Vector3D* DrawCommonData::getpDirectionalLightVector()
{
	return &directional_light_vector_;
}



RenderTexture* DrawCommonData::getpRenderTextureMain()
{
	return &main_;
}



RenderTexture* DrawCommonData::getpRenderTextureMotionBlur()
{
	return &motion_blur_;
}



//****************************************
// 関数定義
//****************************************
void DrawCommonData::Init()
{
	main_.Init(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
	motion_blur_.Init(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
}



void DrawCommonData::Uninit()
{
	main_.Uninit();
	motion_blur_.Uninit();
}