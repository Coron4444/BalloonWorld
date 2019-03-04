//================================================================================
//!	@file	 RenderTexture.h
//!	@brief	 �����_�[�e�N�X�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



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
	LPDIRECT3DTEXTURE9 texture_ = nullptr;			//!< �e�N�X�`��
	LPDIRECT3DSURFACE9 surface_ = nullptr;			//!< �T�[�t�F�X
	LPDIRECT3DSURFACE9 stencil_surface_ = nullptr;	//!< �X�e���V���T�[�t�F�X
	D3DVIEWPORT9 view_port_;						//!< �r���[�|�[�g
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< �f�o�C�X

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
	//! @brief �X�e���V���T�[�t�F�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DSURFACE9 �X�e���V���T�[�t�F�X
	//----------------------------------------
	LPDIRECT3DSURFACE9 getpStencilSurface();

	//----------------------------------------
	//! @brief �X�e���V���T�[�t�F�X�ݒ�֐�
	//! @details
	//! @param value �X�e���V���T�[�t�F�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setStencilSurface(LPDIRECT3DSURFACE9 value);

	//----------------------------------------
	//! @brief �r���[�|�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval D3DVIEWPORT9 �r���[�|�[�g
	//----------------------------------------
	D3DVIEWPORT9* getpViewPort();

	//----------------------------------------
	//! @brief �r���[�|�[�g�ݒ�֐�
	//! @details
	//! @param value �r���[�|�[�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setViewPort(D3DVIEWPORT9 value);

	//----------------------------------------
	//! @brief �����_�[�^�[�Q�b�g�ݒ�֐�
	//! @details
	//! @param render_target_index �����_�[�^�[�Q�b�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRenderTarget(int render_target_index);

	//----------------------------------------
	//! @brief �X�e���V���T�[�t�F�X&�r���[�|�[�g�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void setStencilSurfaceAndViewPort();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param texture_width  �Ȃ�
	//! @param texture_height �Ȃ�
	//! @param format         �t�H�[�}�b�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(int texture_width, int texture_height, _D3DFORMAT format = D3DFMT_A8R8G8B8);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();
};



#endif
