//================================================================================
//!	@file	 InputManager.h
//!	@brief	 �C���v�b�g�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/03
//================================================================================
#ifndef	_INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../Controller.h"
#include "../Keyboard.h"



//************************************************************														   
//! @brief   �C���v�b�g�}�l�[�W��Class(Singleton)
//!
//! @details �C���v�b�g�}�l�[�W��Class(Singleton)
//************************************************************
class InputManager
{
//====================
// static�ϐ�
//====================
private:
	static InputManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval InputManager* �C���X�^���X
	//----------------------------------------
	static InputManager* getpInstance();


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
	Controller* controller_;	//!< �R���g���[���[
	Keyboard* keyboard_;		//!< �L�[�{�[�h


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �R���g���[���[�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Controller* �R���g���[���[
	//----------------------------------------
	Controller* getpController();

	//----------------------------------------
	//! @brief �L�[�{�[�h�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Keyboard* �L�[�{�[�h
	//----------------------------------------
	Keyboard* getpKeyboard();


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	InputManager();

public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param hInstance �C���X�^���X�n���h��
	//! @param hWnd      �E�B���h�E�n���h��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(HINSTANCE hInstance, HWND hWnd);

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


//====================
// �����ς݊֐�
//====================
private:
	InputManager(const InputManager& class_name) = delete;
	InputManager& operator = (const InputManager& class_name) = delete;
};



#endif
