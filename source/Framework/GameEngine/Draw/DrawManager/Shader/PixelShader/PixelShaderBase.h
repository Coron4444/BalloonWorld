//================================================================================
//!	@file	 PixelShaderBase.h
//!	@brief	 �s�N�Z���V�F�[�_�[BassClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_PIXEL_SHADER_BASE_H_
#define _PIXEL_SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include "../ShaderBase.h"



//****************************************
// �N���X�錾
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   �s�N�Z���V�F�[�_�[BassClass
//!
//! @details �s�N�Z���V�F�[�_�[��BassClass
//************************************************************
class PixelShaderBase : public ShaderBase
{
//====================
// �萔
//====================
private:
	static const std::string DEFAULT_TEXTURE_NAME;		//!< �f�t�H���g�e�N�X�`����


//====================
// �ϐ�
//====================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< �s�N�Z���V�F�[�_�[
	TextureObject* default_texture_ = nullptr;			//!< �f�t�H���g�e�N�X�`���I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DPIXELSHADER9 �s�N�Z���V�F�[�_�[
	//----------------------------------------
	LPDIRECT3DPIXELSHADER9 getpPixelShader();

	//----------------------------------------
	//! @brief �f�t�H���g�e�N�X�`���n���h���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DTEXTURE9 �f�t�H���g�e�N�X�`���n���h��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDefaultTexture();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�t�H���g�e�N�X�`���n���h���������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitDefaultTexture();

	//----------------------------------------
	//! @brief �f�o�C�X�ɃV�F�[�_�[�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ShaderSetToDevice() override;

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�R���p�C���֐�
	//! @details
	//! @param *file_name      �t�@�C����
	//! @param *entry_function �G���g���֐���
	//! @param *version        �V�F�[�_�[�o�[�W����
	//! @retval bool �R���p�C�������Ȃ�true
	//----------------------------------------
	bool PixelShaderCompile(const char* file_name,
							const char* entry_function,
							const char* version);

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleasePixelShader();
};



#endif
