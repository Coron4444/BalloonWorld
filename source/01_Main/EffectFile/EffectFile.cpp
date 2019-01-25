//================================================================================
//
//    �G�t�F�N�g�t�@�C���w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/04
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "EffectFile.h"

#include <stdio.h>




//**********************************************************************
//
// �ÓI�����o�ϐ���`
//
//**********************************************************************

EffectFile* EffectFile::effect_file_ = nullptr;



//**********************************************************************
//
// �ÓI�����o�֐���`
//
//**********************************************************************

EffectFile* EffectFile::GetPointer()
{
	return effect_file_;
}



void EffectFile::Create()
{
	effect_file_ = new EffectFile;
}



void EffectFile::Delete()
{
	delete effect_file_;
}



//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************

//================================================================================
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//================================================================================

EffectFile::EffectFile()
	: effect_(nullptr)
{
	InputEffectFile();
}



//================================================================================
//
// [ �f�X�g���N�^ ]
//
//================================================================================

EffectFile::~EffectFile()
{
	// �e��J��
	SafeRelease(&effect_);
}



//================================================================================
//
// [ �G�t�F�N�g�t�@�C���̓ǂݍ��݊֐� ]
//
//================================================================================

void EffectFile::InputEffectFile()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = RendererDirectX9::GetDevice();
	assert(device != nullptr && "Device�̎擾�Ɏ��s(EffectFile.cpp)");

	// �V�F�[�_�[�̓ǂݍ���
	FILE* fp;
	fp = fopen("resource/HLSL/AnimationFBX.obj", "rb");
	
	if (fp == nullptr) return;
	
	// �t�@�C���T�C�Y�擾
	fseek(fp, 0, SEEK_END);
	unsigned size = (unsigned)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// �t�@�C���f�[�^�擾
	char* src_data = new char[size];
	fread(src_data, size, sizeof(char), fp);
	fclose(fp);

	LPD3DXBUFFER error = nullptr;
	// �G�t�F�N�g�t�@�C���̃R���p�C��
	HRESULT hr = D3DXCreateEffect(device,		// �f�o�C�X
		                          src_data,		// �R���p�C���ς�fx�f�[�^
		                          size,			// �R���p�C���ς�fx�f�[�^�̃T�C�Y
		                          NULL,			// �v���v���Z�b�T��`�ւ̃|�C���^
		                          NULL,			// �I�v�V�����̃C���^�t�F�[�X�ւ̃|�C���^
		                          0,			// D3DXSHADER�Ŏ��ʂ����R���p�C���I�v�V����
		                          NULL,			// ���L�����Ŏg��ID3DXEffectPool�I�u�W�F�N�g�ւ̃|�C���^
		                          &effect_,		// �R���p�C�����ꂽ�G�t�F�N�g�̊i�[��
		                          &error);		// �R���p�C���G���[�ꗗ�̊i�[��

	if (FAILED(hr))
	{
		MessageBox( NULL, (LPCTSTR)error->GetBufferPointer(), "�G���[", MB_OK );
		return;
	}

	// �e��J��
	SafeRelease(&error);
	delete[] src_data;
}