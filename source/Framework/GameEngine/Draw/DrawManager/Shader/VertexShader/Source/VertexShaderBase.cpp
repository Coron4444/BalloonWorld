//================================================================================
//!	@file	 VertexShaderBase.cpp
//!	@brief	 ���_�V�F�[�_�[BaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
LPDIRECT3DVERTEXSHADER9 VertexShaderBase::getpVertexShader()
{
	return vertex_shader_;
}



//****************************************
// �֐���`
//****************************************
void VertexShaderBase::ShaderSetToDevice()
{
	getpDevice()->SetVertexShader(vertex_shader_);
}



bool VertexShaderBase::VertexShaderCompile(const char* file_name,
										   const char* entry_function,
										   const char* version)
{
	LPD3DXBUFFER compiled_code;
	bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
												version, &compiled_code);
	if (!is_compile) return false;

	HRESULT hr = getpDevice()
		->CreateVertexShader((DWORD*)compiled_code->GetBufferPointer(),
							 &vertex_shader_);

	// ����������
	if (SUCCEEDED(hr)) return true;

	// �G���[���b�Z�[�W
	MessageBox(nullptr, "���_�V�F�[�_�[�쐬���s", "Error", MB_OK);
	return false;
}



void VertexShaderBase::ReleaseVertexShader()
{
	SafeRelease::PlusRelease(&vertex_shader_);
}