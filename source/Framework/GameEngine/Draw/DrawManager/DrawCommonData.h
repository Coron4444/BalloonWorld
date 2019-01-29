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
	RenderTexture motion_blur_;		//!< ���[�V�����u���[�p�����_�[�e�N�X�`��


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
	//! @brief ���[�V�����u���[�p�����_�[�e�N�X�`���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RenderTexture* ���[�V�����u���[�p�����_�[�e�N�X�`��
	//----------------------------------------
	RenderTexture* getpRenderTextureMotionBlur();

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