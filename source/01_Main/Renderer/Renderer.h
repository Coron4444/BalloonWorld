//================================================================================
//!	@file	 Renderer.h
//!	@brief	 �����_���[Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_H_
#define _RENDERE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Renderer/RendererDirectX9/RendererDirectX9.h>



//****************************************
// �N���X�錾
//****************************************
class RendererInterface;
class RendererFactoryInterface;



//************************************************************														   
//! @brief   �����_���[Class
//!
//! @details �����_���[��Class(Singleton)
//************************************************************
class Renderer
{
//====================
// �񋓌^��`
//====================
public:
	enum MODE
	{
		NONE = -1,
		DIRECTX9,
		DIRECTX11,
		OPEN_GL,
		MAX
	};


//====================
// static�ϐ�
//====================
private:
	static Renderer* instance_;				//!< �C���X�^���X
	static RendererInterface* renderer_;	//!< �����_���[


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Renderer* �����_���[�C���X�^���X
	//----------------------------------------
	static Renderer* getpInstance();


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	static void ReleaseInstance();

	
//====================
// �ϐ�
//====================
private:
	MODE mode_ = MODE::NONE;	//!< ���[�h


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �����_���[�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RendererInterface* �����_���[
	//----------------------------------------
	RendererInterface* getpRenderer();

	//----------------------------------------
	//! @brief �����_���[�ݒ�֐�
	//! @details
	//! @param *factory �����_���[�t�@�N�g���[
	//! @param *mode    �����_���[���[�h
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRenderer(RendererFactoryInterface* factory, MODE mode);

	//----------------------------------------
	//! @brief �C���^�[�t�F�[�X�擾�֐�
	//! @details
	//! @param **out_pointer �擾�p
	//! @retval void �Ȃ�
	//----------------------------------------
	template <class Type>
	void getInterface(Type** out_pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*out_pointer = ((RendererDirectX9*)renderer_)->getpInterface();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

	//----------------------------------------
	//! @brief �f�o�C�X�擾�֐�
	//! @details
	//! @param **out_pointer �擾�p
	//! @retval void �Ȃ�
	//----------------------------------------
	template <class Type>
	void getDevice(Type** out_pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*out_pointer = ((RendererDirectX9*)renderer_)->getpDevice();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Renderer();

public:
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
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	bool DrawBegin();

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @details
	//! @param is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawEnd(bool is_begin_scene);

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Present();


//====================
// �����ς݊֐�
//====================
private:
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;
};



#endif