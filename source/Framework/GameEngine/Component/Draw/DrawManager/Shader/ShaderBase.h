//================================================================================
//!	@file	 ShaderBase.h
//!	@brief	 �V�F�[�_�[BaseClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_SHADER_BASE_H_
#define _SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Renderer/Renderer.h>



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class Camera;



//************************************************************														   
//! @brief   �V�F�[�_�[BaseClass
//!
//! @details �V�F�[�_�[��BaseClass
//************************************************************
class ShaderBase
{
//====================
// �ϐ�
//====================
private:
	LPD3DXCONSTANTTABLE	constant_table_ = nullptr;	//!< �萔�e�[�u��
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< �f�o�C�X


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �萔�e�[�u���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPD3DXCONSTANTTABLE �萔�e�[�u��
	//----------------------------------------
	LPD3DXCONSTANTTABLE getpConstantTable();

protected:
	//----------------------------------------
	//! @brief �f�o�C�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DDEVICE9 �f�o�C�X
	//----------------------------------------
	LPDIRECT3DDEVICE9 getpDevice();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�X�g���N�^�֐�
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~ShaderBase() = 0;

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param *camera      �J����
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ObjectSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) = 0;

	//----------------------------------------
	//! @brief ���b�V���ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param *camera      �J����
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void MeshSetting(DrawBase* draw, Camera* camera,
							 unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief �f�o�C�X�ɃV�F�[�_�[�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ShaderSetToDevice() = 0;

protected:
	//----------------------------------------
	//! @brief �V�F�[�_�[�R���p�C���֐�
	//! @details
	//! @param *file_name : �t�@�C����
	//! @param *entry_function : �G���g���֐���
	//! @param *version : �V�F�[�_�[�o�[�W����
	//! @param *compiled_code : �R���p�C���ς݃R�[�h
	//! @retval bool �R���p�C�������Ȃ�true
	//----------------------------------------
	bool ShaderCompile(const char* file_name, const char* entry_function,
					   const char* version, LPD3DXBUFFER* compiled_code);

	//----------------------------------------
	//! @brief �f�o�C�X�������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitDevice();
};

#endif
