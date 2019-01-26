//================================================================================
//!	@file	 VertexShaderBumpMapping.h
//!	@brief	 �o���v�}�b�s���O���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_BUMP_MAPPING_H_
#define _VERTEX_SHADER_BUMP_MAPPING_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderNull/VertexShaderNull.h"

#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class ModelXObject;



//************************************************************														   
//! @brief   �o���v�}�b�s���O���_�V�F�[�_�[Class
//!
//! @details �o���v�}�b�s���O�̒��_�V�F�[�_�[Class
//************************************************************
class VertexShaderBumpMapping : public VertexShaderNull
{
//====================
// �萔
//====================
private:
	static const D3DVERTEXELEMENT9 DECLARATION[];	//!< ���_�錾
	static const char* PATH;						//!< �t�@�C���p�X


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief ���_�錾�p���b�V���X�V�֐�
	//! @details
	//! @param model_x X���f���I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	static void UpdateMeshDeclaration(ModelXObject* model_x);


//====================
// �ϐ�
//====================
private:
	MATRIX math_matrix_;										//!< �v�Z�p�s��
	IDirect3DVertexDeclaration9* declaration_object_ = nullptr;	//!< ���_�錾


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
