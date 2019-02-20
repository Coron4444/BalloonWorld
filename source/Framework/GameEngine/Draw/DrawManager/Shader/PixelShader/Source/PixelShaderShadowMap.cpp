//================================================================================
//!	@file	 PixelShaderShadowMap.cpp
//!	@brief	 �V���h�E�}�b�v�s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderShadowMap.h"



//****************************************
// �萔��`
//****************************************
const char* PixelShaderShadowMap::PATH = "resource/HLSL/Effect/PixelShader/ShadowMap.psh";



//****************************************
// �֐���`
//****************************************
void PixelShaderShadowMap::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderShadowMap::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}