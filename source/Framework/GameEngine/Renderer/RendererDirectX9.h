//================================================================================
//!	@file	 RendererDirectX9.h
//!	@brief	 �����_���[DirectX9Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_DIRECTX9_H_
#define _RENDERE_DIRECTX9_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <d3d9.h>
#include <d3dx9.h>

#include "RendererInterface.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief �����_���[DirectX9Class
//!
//! @details DirectX9�p�����_���[Class
//************************************************************
class RendererDirectX9 : public RendererInterface
{
//====================
// �N���X��`
//====================
public:
	//****************************************														   
	//! @brief ���_Class
	//!
	//! @details ���_�p��Class
	//****************************************
	class VERTEX_3D
	{
	//====================
	// �ϐ�
	//====================
	public:
		Vec3   posisiont_;	//!< ���W
		Vec3   normal_;		//!< �@��
		Color4 color_;		//!< �J���[
		Vec2   texcoord_;	//!< �e�N�X�`�����W
	};


//====================
// �萔
//====================
public:
	static const DWORD FVF_VERTEX_3D;	//!< FVF


//====================
// �ϐ�
//====================
private:
	LPDIRECT3D9        direct3d_interface_ = nullptr;	//!< �C���^�[�t�F�[�X
	LPDIRECT3DDEVICE9  direct3d_device_ = nullptr;		//!< �f�o�C�X


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���^�[�t�F�[�X�|�C���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3D9 �C���^�t�F�[�X
	//----------------------------------------
	LPDIRECT3D9 getpInterface();

	//----------------------------------------
	//! @brief �f�o�C�X�|�C���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LPDIRECT3DDEVICE9 �f�o�C�X
	//----------------------------------------
	LPDIRECT3DDEVICE9 getpDevice();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details �C���^�[�t�F�[�X�y�уf�o�C�X�̐���
	//! @param hInstance	  �C���X�^���X�n���h��
	//! @param hWnd			  Windows�n���h��
	//! @param is_full_screen �t���X�N���[���t���O
	//! @param window_width	  �E�B���h�E��
	//! @param window_height  �E�B���h�E����
	//! @retval bool �����������̗L��
	//----------------------------------------
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height) override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details �e��J��
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @details
	//! @param clear_color �N���A�F
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	bool DrawBegin(XColor4 clear_color = {0.123f, 0.25f, 0.75f, 1.0f}) override;

	//----------------------------------------
	//! @brief �N���A���`��J�n�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	bool NoClearDrawBegin() override;

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @details
	//! @param is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawEnd(bool is_begin_scene) override;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Present() override;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UseAlphaBlending(bool flag);

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���`����)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Linear();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���Z����)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Add();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���Z����)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Sub();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(��Z����)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Mul();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�Ă����ݍ���)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Baking();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�l�K�|�W���]����)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Nega();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�s��������)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Opacity();

	//----------------------------------------
	//! @brief �f�t�H���g�T���v���[�X�e�[�g�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetDefaultSamplerState();
};



#endif