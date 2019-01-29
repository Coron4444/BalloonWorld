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
#include "../ShaderBase.h"



//************************************************************														   
//! @brief   �s�N�Z���V�F�[�_�[BassClass
//!
//! @details �s�N�Z���V�F�[�_�[��BassClass
//************************************************************
class PixelShaderBase : public ShaderBase
{
//====================
// �ϐ�
//====================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< �s�N�Z���V�F�[�_�[


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


//====================
// �֐�
//====================
public:
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
