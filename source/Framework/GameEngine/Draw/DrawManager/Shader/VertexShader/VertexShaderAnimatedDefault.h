//================================================================================
//!	@file	 VertexShaderAnimatedDefault.h
//!	@brief	 �A�j���[�V�����t���f�t�H���g���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_ANIMATED_DEFAULT_H_
#define _VERTEX_SHADER_ANIMATED_DEFAULT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderNull.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �A�j���[�V�����t���f�t�H���g���_�V�F�[�_�[Class
//!
//! @details �A�j���[�V�����t���f�t�H���g�̒��_�V�F�[�_�[Class
//************************************************************
class VertexShaderAnimatedDefault : public VertexShaderNull
{
//====================
// �萔
//====================
private:
	static const D3DVERTEXELEMENT9 VERTEX_DECLARATION[];	//!< ���_�錾�z��
	static const char* PATH;			//!< �t�@�C���p�X
	static const int MAX_BONE_NUM = 55;	//!< �ő�{�[����


//====================
// �ϐ�
//====================
private:
	IDirect3DVertexDeclaration9* vertex_declaration_ = nullptr;		//!< ���_�錾
	MATRIX bone_matrix_[MAX_BONE_NUM];								//!< �{�[���s��


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
