//================================================================================
//!	@file	 PixelShaderBlinnPhong.h
//!	@brief	 �u�����E�t�H���̋��ʔ��˃s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================
#ifndef	_PIXEL_SHADER_BLINN_PHONG_H_
#define _PIXEL_SHADER_BLINN_PHONG_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "PixelShaderNull.h"



//************************************************************														   
//! @brief   �u�����E�t�H���̋��ʔ��˃s�N�Z���V�F�[�_�[Class
//!
//! @details �u�����E�t�H���̋��ʔ��˂̃s�N�Z���V�F�[�_�[��Class
//************************************************************
class PixelShaderBlinnPhong : public PixelShaderNull
{
//====================
// �萔
//====================
private:
	static const char* PATH;	//!< �t�@�C���p�X


//====================
// �ϐ�
//====================
private:
	D3DXMATRIX math_matrix_;		//!< �v�Z�p�s��


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param *camera      �J����
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief ���b�V���ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param *camera      �J����
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void MeshSetting(DrawBase* draw, Camera* camera,
					 unsigned object_index, unsigned mesh_index);
};



#endif
