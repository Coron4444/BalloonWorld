//================================================================================
//!	@file	 PixelShaderDefaultShadowShadow.cpp
//!	@brief	 �f�t�H���g�e�s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderDefaultShadow.h"



//****************************************
// �萔��`
//****************************************
const char* PixelShaderDefaultShadow::PATH = "resource/HLSL/Effect/PixelShader/DefaultShadow.psh";



//****************************************
// �֐���`
//****************************************
void PixelShaderDefaultShadow::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �f�t�H���g�e�N�X�`��������
	InitDefaultTexture();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderDefaultShadow::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}



void PixelShaderDefaultShadow::ObjectSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderDefaultShadow::MeshSetting(DrawBase* draw, Camera* camera,
									 unsigned object_index,
									 unsigned mesh_index)
{
	camera = camera;

	// �f�B�t�[�Y�e�N�X�`��
	int sampler_index = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	if (draw->getpDiffuseTexture(object_index, mesh_index) == nullptr)
	{
		getpDevice()->SetTexture(sampler_index, getpDefaultTexture());
	}
	else
	{
		getpDevice()->SetTexture(sampler_index,
								 draw->getpDiffuseTexture(object_index, mesh_index));
	}

	// �V���h�E�}�b�v�e�N�X�`��
	sampler_index = getpConstantTable()->GetSamplerIndex("SHADOW_MAP_SAMPLER");
	getpDevice()->SetTexture(sampler_index, getpDrawCommonData()
							 ->getpRenderTextureShadowMap()->getpTexture());
}