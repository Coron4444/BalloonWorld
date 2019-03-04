//================================================================================
//!	@file	 DrawCommonData.h
//!	@brief	 �`�拤�ʃf�[�^Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_DRAW_COMMON_DATA_H_
#define _DRAW_COMMON_DATA_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "RenderTexture.h"

#include <Tool/Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class Camera;


//************************************************************														   
//! @brief   �`�拤�ʃf�[�^Class
//!
//! @details �`��̋��ʃf�[�^Class
//************************************************************
class DrawCommonData
{	
//====================
// �ϐ�
//====================
private:
	Vector3D directional_light_vector_ = {0.5f, -1.0f, 0.8f};	//!< �g�U���ˏƖ��x�N�g��
	RenderTexture main_;			//!< ���C���p�����_�[�e�N�X�`��
	RenderTexture shadow_map_;		//!< �V���h�E�}�b�v�p�����_�[�e�N�X�`��
	RenderTexture motion_blur_;		//!< ���[�V�����u���[�p�����_�[�e�N�X�`��
	Camera* camera_shadow_map_;		//!< �V���h�E�}�b�v�p�J����



//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �g�U���ˏƖ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �g�U���ˏƖ��x�N�g��
	//----------------------------------------
	Vector3D* getpDirectionalLightVector();

	//----------------------------------------
	//! @brief ���C���p�����_�[�e�N�X�`���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RenderTexture* ���C���p�����_�[�e�N�X�`��
	//----------------------------------------
	RenderTexture* getpRenderTextureMain();

	//----------------------------------------
	//! @brief �V���h�E�}�b�v�p�����_�[�e�N�X�`���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RenderTexture* �V���h�E�}�b�v�p�����_�[�e�N�X�`��
	//----------------------------------------
	RenderTexture* getpRenderTextureShadowMap();

	//----------------------------------------
	//! @brief ���[�V�����u���[�p�����_�[�e�N�X�`���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RenderTexture* ���[�V�����u���[�p�����_�[�e�N�X�`��
	//----------------------------------------
	RenderTexture* getpRenderTextureMotionBlur();

	//----------------------------------------
	//! @brief �V���h�E�}�b�v�p�J�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Camera* �V���h�E�}�b�v�p�J����
	//----------------------------------------
	Camera* getpCameraShadowMap();

	//----------------------------------------
	//! @brief �V���h�E�}�b�v�p�J�����擾�֐�
	//! @details
	//! @param value �V���h�E�}�b�v�p�J����
	//! @retval void �Ȃ� 
	//----------------------------------------
	void setCameraShadowMap(Camera* value);


//====================
// �֐���`
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
};



#endif