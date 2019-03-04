//================================================================================
//!	@file	 VertexShaderShadowMap.cpp
//!	@brief	 �V���h�E�}�b�v���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderShadowMap.h"



//****************************************
// �萔��`
//****************************************
const char* VertexShaderShadowMap::PATH = "resource/HLSL/Effect/VertexShader/ShadowMap.vsh";



//****************************************
// �֐���`
//****************************************
void VertexShaderShadowMap::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderShadowMap::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();
}



void VertexShaderShadowMap::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// �s��
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());
}