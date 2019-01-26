//================================================================================
//!	@file	 PixelShaderDefault.cpp
//!	@brief	 �f�t�H���g�s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/21
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PixelShaderDefault.h"

#include <GameObjectManager/GameObjectManager.h>



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
	draw = draw;
	object_index = object_index;
	mesh_index = mesh_index;
	// �f�B�q���[�Y�e�N�X�`���̐ݒ�
	int diffuse_sampler_ = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	LPDIRECT3DTEXTURE9 diffuse_texture = draw->getpDiffuseTexture(object_index, mesh_index);
	bool is_texture = diffuse_texture != nullptr;
	getpConstantTable()->SetBool(getpDevice(), "IS_TEXTURE", is_texture);
	getpDevice()->SetTexture(diffuse_sampler_, diffuse_texture);
}