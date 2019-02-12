//================================================================================
//!	@file	 ShaderBase.cpp
//!	@brief	 �V�F�[�_�[BaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ShaderBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
LPD3DXCONSTANTTABLE ShaderBase::getpConstantTable()
{
	return constant_table_; 
}



LPDIRECT3DDEVICE9 ShaderBase::getpDevice()
{
	return device_; 
}



DrawCommonData* ShaderBase::getpDrawCommonData()
{
	return common_data_;
}



void ShaderBase::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



//****************************************
// �֐���`
//****************************************
ShaderBase::~ShaderBase()
{

}



bool ShaderBase::ShaderCompile(const char* file_name, const char* entry_function,
							   const char* version, LPD3DXBUFFER* compiled_code)
{
	LPD3DXBUFFER compil_error = nullptr;
	HRESULT hr = D3DXCompileShaderFromFile(file_name,			// �t�@�C����
										   nullptr,				// �v���v���Z�b�T��`�ւ̃|�C���^
										   nullptr,				// ID3DXInclude(#include�^������)
										   entry_function,		// �G���g���֐���
										   version,				// �V�F�[�_�[�o�[�W����
										   0,					// �R���p�C���I�v�V����
										   compiled_code,		// �R���p�C���ς݃R�[�h
										   &compil_error,		// �G���[���
										   &constant_table_);	// �R���X�^���g�e�[�u��
																
	// ����������
	if (SUCCEEDED(hr))
	{
		SafeRelease::PlusRelease(&compil_error);
		return true;
	}
		

	// �G���[���b�Z�[�W
	if (compil_error)
	{
		// �R���p�C���G���[����
		MessageBox(NULL, (LPSTR)compil_error->GetBufferPointer(), "Error", MB_OK);
	}
	else
	{
		// ���̑��̃G���[
		MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǂݍ��߂܂���", "Error", MB_OK);
	}

	SafeRelease::PlusRelease(&compil_error);
	return false;
}



void ShaderBase::InitDevice()
{
	// �f�o�C�X�̎擾
	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(VertexShaderBase.cpp)", "Error", MB_OK);
		return;
	}
}



void ShaderBase::ReleaseConstantTable()
{
	SafeRelease::PlusRelease(&constant_table_);
}