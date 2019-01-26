//================================================================================
//!	@file	 VertexShaderFixed.h
//!	@brief	 �Œ�@�\���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_VERTEX_SHADER_FIXED_H_
#define _VERTEX_SHADER_FIXED_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderNull/VertexShaderNull.h"



//****************************************
// �N���X�錾
//****************************************
class Camera;
class DrawBase;



//************************************************************														   
//! @brief   �Œ�@�\���_�V�F�[�_�[Class
//!
//! @details �Œ�@�\�̒��_�V�F�[�_�[Class
//************************************************************
class VertexShaderFixed : public VertexShaderNull
{
//====================
// �ϐ�
//====================
private:
	D3DLIGHT9 directional_light_;	//!< �f�B���N�V���i�����C�g


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

private:
	//----------------------------------------
	//! @brief �e�N�X�`���ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetTexture(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief �}�e���A���ݒ�֐�
	//! @details
	//! @param *draw        �`����N���X
	//! @param object_index �`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetMaterial(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief �g�U�Ɩ��X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateDirectionalLignt();
};



#endif
