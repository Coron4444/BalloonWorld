//================================================================================
//!	@file	 GameEngine.h
//!	@brief	 �Q�[���G���W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_GAME_ENGINE_H_
#define _GAME_ENGINE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>



//****************************************
// �N���X�錾
//****************************************
class SceneManager;



//************************************************************														   
//! @brief   �Q�[��EngineClass
//!
//! @details �Q�[���V�X�e���S�̂��Ǘ�����
//! @details Renderer�ASceneManager�A
//! @details Input�ASound�ADebuger�����Ǘ�����
//************************************************************
class GameEngine
{
//====================
// �萔
//====================
public:
	static const unsigned SCREEN_WIDTH;
	static const unsigned SCREEN_HEIGHT;


//====================
// �ϐ�
//====================
private:
	SceneManager* scene_manager_ = nullptr;		//!< �V�[���Ǘ���
	


//====================
// �֐�
//====================
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
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief ��X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void LateUpdate();
};



#endif