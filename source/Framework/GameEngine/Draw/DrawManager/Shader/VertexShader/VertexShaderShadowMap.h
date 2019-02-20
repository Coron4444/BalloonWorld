//================================================================================
//!	@file	 VertexShaderShadowMap.h
//!	@brief	 �V���h�E�}�b�v���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_VERTEX_SHADER_SHADOW_MAP_H_
#define _VERTEX_SHADER_SHADOW_MAP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderNull.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �V���h�E�}�b�v���_�V�F�[�_�[Class
//!
//! @details �V���h�E�}�b�v�̒��_�V�F�[�_�[Class
//************************************************************
class VertexShaderShadowMap : public VertexShaderNull
{
//====================
// �萔
//====================
private:
	static const char* PATH;		//!< �t�@�C���p�X


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
};



#endif
