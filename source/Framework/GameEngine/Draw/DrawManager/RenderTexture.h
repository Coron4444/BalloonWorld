//================================================================================
//!	@file	 RenderTexture.h
//!	@brief	 �����_�[�e�N�X�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../Renderer/Renderer.h"



//************************************************************														   
//! @brief   �����_�[�e�N�X�`��Class
//!
//! @details �����_�[�e�N�X�`����Class
//************************************************************
class RenderTexture
{
//====================
// �ϐ�
//====================
private:
	LPDIRECT3DTEXTURE9 texture_ = nullptr;		//!< �e�N�X�`��
	LPDIRECT3DSURFACE9 surface_ = nullptr;		//!< �T�[�t�F�X
	LPDIRECT3DDEVICE9 device_ = nullptr;		//!< �f�o�C�X


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �e�N�X�`���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DTEXTURE9 �e�N�X�`��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpTexture();

	//----------------------------------------
	//! @brief �e�N�X�`���ݒ�֐�
	//! @details
	//! @param value �e�N�X�`��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTexture(LPDIRECT3DTEXTURE9 value);

	//----------------------------------------
	//! @brief �T�[�t�F�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DSURFACE9 �T�[�t�F�X
	//----------------------------------------
	LPDIRECT3DSURFACE9 getpSurface();

	//----------------------------------------
	//! @brief �T�[�t�F�X�ݒ�֐�
	//! @details
	//! @param value �T�[�t�F�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setSurface(LPDIRECT3DSURFACE9 value);

	//----------------------------------------
	//! @brief �����_�[�^�[�Q�b�g�ݒ�֐�
	//! @details
	//! @param render_target_index �����_�[�^�[�Q�b�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRenderTarget(int render_target_index);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param texture_width �Ȃ�
	//! @param texture_height �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(int texture_width, int texture_height);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();
};



#endif
