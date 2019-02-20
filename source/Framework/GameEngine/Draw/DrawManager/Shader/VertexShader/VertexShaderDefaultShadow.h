//================================================================================
//!	@file	 VertexShaderDefaultShadow.h
//!	@brief	 �f�t�H���g�e���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_VERTEX_SHADER_DEFAULT_SHADOW_H_
#define _VERTEX_SHADER_DEFAULT_SHADOW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderNull.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �f�t�H���g�e���_�V�F�[�_�[Class
//!
//! @details �f�t�H���g�e�̒��_�V�F�[�_�[Class
//************************************************************
class VertexShaderDefaultShadow : public VertexShaderNull
{
//====================
// �萔
//====================
private:
	static const char* PATH;					//!< �t�@�C���p�X
	static const float OFF_SET_X;				//!< X���W�I�t�Z�b�g�l
	static const float OFF_SET_Y;				//!< Y���W�I�t�Z�b�g�l
	static const MATRIX TEXTURE_PROJECTION;		//!< �e�N�X�`�����W


//====================
// �ϐ�
//====================
private:
	MATRIX math_matrix_;	//!< �v�Z�p�s��


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
