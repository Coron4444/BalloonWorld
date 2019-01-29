//================================================================================
//!	@file	 PixelShaderBase.cpp
//!	@brief	 �s�N�Z���V�F�[�_�[BassClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
LPDIRECT3DPIXELSHADER9 PixelShaderBase::getpPixelShader()
{
	return pixel_shader_;
}



//****************************************
// �֐���`
//****************************************
void PixelShaderBase::ShaderSetToDevice()
{
	getpDevice()->SetPixelShader(pixel_shader_);
}



bool PixelShaderBase::PixelShaderCompile(const char* file_name,
										 const char* entry_function,
										 const char* version)
{
	LPD3DXBUFFER compiled_code;
	bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
												version, &compiled_code);
	if (!is_compile) return false;

	HRESULT hr = getpDevice()
		->CreatePixelShader((DWORD*)compiled_code->GetBufferPointer(),
							&pixel_shader_);

	// ����������
	if (SUCCEEDED(hr)) return true;

	// �G���[���b�Z�[�W
	MessageBox(nullptr, "�s�N�Z���V�F�[�_�[�쐬���s", "Error", MB_OK);
	return false;
}



void PixelShaderBase::ReleasePixelShader()
{
	SafeRelease::PlusRelease(&pixel_shader_);
}