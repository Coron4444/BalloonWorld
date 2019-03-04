//================================================================================
//!	@file	 PixelShaderDefault.cpp
//!	@brief	 �f�t�H���g�s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/21
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderDefault.h"



//****************************************
// �萔��`
//****************************************
const char* PixelShaderDefault::PATH = "resource/HLSL/Effect/PixelShader/Default.psh";



//****************************************
// �֐���`
//****************************************
void PixelShaderDefault::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �f�t�H���g�e�N�X�`��������
	InitDefaultTexture();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderDefault::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}



void PixelShaderDefault::ObjectSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderDefault::MeshSetting(DrawBase* draw, Camera* camera,
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
}