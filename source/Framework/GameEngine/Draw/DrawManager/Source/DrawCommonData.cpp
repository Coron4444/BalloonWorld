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
#include "../../../GameEngine.h"


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



RenderTexture* DrawCommonData::getpRenderTextureMotionBlur()
{
	return &motion_blur_;
}



//****************************************
// �֐���`
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