//================================================================================
//!	@file	 DrawCommonData.cpp
//!	@brief	 �`�拤�ʃf�[�^Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../DrawCommonData.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* DrawCommonData::getpDirectionalLightVector()
{
	return &directional_light_vector_;
}



RenderTexture* DrawCommonData::getpRenderTextureMain()
{
	return &main_;
}



RenderTexture* DrawCommonData::getpRenderTextureShadowMap()
{
	return &shadow_map_;
}



RenderTexture* DrawCommonData::getpRenderTextureMotionBlur()
{
	return &motion_blur_;
}



Camera* DrawCommonData::getpCameraShadowMap()
{
	return camera_shadow_map_;
}



void DrawCommonData::setCameraShadowMap(Camera* value)
{
	camera_shadow_map_ = value;
}



//****************************************
// �֐���`
//****************************************
void DrawCommonData::Init()
{
	main_.Init(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
	shadow_map_.Init(1024* 10, 1024*10, D3DFMT_R32F);// GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);// , D3DFMT_R32F);
	motion_blur_.Init(GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT);
}



void DrawCommonData::Uninit()
{
	main_.Uninit();
	shadow_map_.Uninit();
	motion_blur_.Uninit();
}