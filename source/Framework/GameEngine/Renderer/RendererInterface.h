//================================================================================
//!	@file	 RendererInterface.h
//!	@brief	 �����_���[InterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_



//****************************************
// �C���N���[�h��
//****************************************



//************************************************************														   
//! @brief   �����_���[InterfaceClass
//!
//! @details �����_���[��InterfaceClass
//************************************************************
class RendererInterface
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~RendererInterface() = 0;
	
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param hInstance	  �C���X�^���X�n���h��
	//! @param hWnd			  Windows�n���h��
	//! @param is_full_screen �t���X�N���[���t���O
	//! @param window_width	  �E�B���h�E��
	//! @param window_height  �E�B���h�E����
	//! @retval bool �����������̗L��
	//----------------------------------------
	virtual bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height) = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @details
	//! @param clear_color �N���A�F
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	virtual bool DrawBegin(XColor4 clear_color = {0.123f, 0.25f, 0.75f, 1.0f}) = 0;

	//----------------------------------------
	//! @brief �N���A���`��J�n�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	virtual bool NoClearDrawBegin() = 0;

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @details
	//! @param is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DrawEnd(bool is_begin_scene) = 0;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Present() = 0;
};



#endif



