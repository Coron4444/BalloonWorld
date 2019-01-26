//================================================================================
//!	@file	 VertexShaderBase.h
//!	@brief	 ���_�V�F�[�_�[BaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_BASE_H_
#define _VERTEX_SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../ShaderBase/ShaderBase.h"



//************************************************************														   
//! @brief   ���_�V�F�[�_�[BassClass
//!
//! @details ���_�V�F�[�_�[��BassClass
//************************************************************
class VertexShaderBase : public ShaderBase
{
//====================
// �ϐ�
//====================
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_ = nullptr;	//!< ���_�V�F�[�_�[


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DVERTEXSHADER9 ���_�V�F�[�_�[
	//----------------------------------------
	LPDIRECT3DVERTEXSHADER9 getpVertexShader();


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
	//! @brief ���_�V�F�[�_�[�R���p�C���֐�
	//! @details
	//! @param *file_name      �t�@�C����
	//! @param *entry_function �G���g���֐���
	//! @param *version        �V�F�[�_�[�o�[�W����
	//! @retval bool �R���p�C�������Ȃ�true
	//----------------------------------------
	bool VertexShaderCompile(const char* file_name,
							 const char* entry_function,
							 const char* version);

	//----------------------------------------
	//! @brief ���_�V�F�[�_�[����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseVertexShader();
};

#endif
