//================================================================================
//!	@file	 Keyboard.h
//!	@brief	 �L�[�{�[�hClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef _KYEBOARD_H_
#define _KYEBOARD_H_



//****************************************
// �C���N���[�h��
//****************************************
#include < dinput.h >



//************************************************************														   
//! @brief   �L�[�{�[�hClass
//!
//! @details �L�[�{�[�h�̓���Class
//************************************************************
class Keyboard
{
//====================
// �萔
//====================
private:
	static const DWORD INPUT_VERSION;			//!< �_�C���N�g�C���v�b�g�o�[�W����
	static const int MAX_KEY_NUM = 256;			//!< �L�[�̍ő吔
	static const int LIMIT_COUNT_REPEAT;		//!< ���s�[�g�J�E���g���~�b�g


//====================
// �ϐ�
//====================
private:
	LPDIRECTINPUT8 direct_input_ = nullptr;		//!< DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 keyboard_ = nullptr;	//!< ���̓f�o�C�X(�L�[�{�[�h)
	BYTE key_state_[MAX_KEY_NUM];				//!< �L�[�{�[�h�̓��͏��
	BYTE key_state_trigger_[MAX_KEY_NUM];		//!< �L�[�{�[�h�̃g���K�[���
	BYTE key_state_repeat_[MAX_KEY_NUM];		//!< �L�[�{�[�h�̃��s�[�g���
	BYTE key_state_release_[MAX_KEY_NUM];		//!< �L�[�{�[�h�̃����[�X���
	int repeat_counter_[MAX_KEY_NUM];			//!< ���s�[�g�J�E���^�[


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �z�[���h��Ԏ擾�֐�
	//! @details
	//! @param value �z�[���h��Ԃ��m�F�������L�[�{�[�h�{�^��ID
	//! @retval bool ������Ă����true
	//----------------------------------------
	bool getHold(int value);

	//----------------------------------------
	//! @brief �g���K�[��Ԏ擾�֐�
	//! @details
	//! @param value �g���K�[��Ԃ��m�F�������L�[�{�[�h�{�^��ID
	//! @retval bool �������u�Ԃ�true
	//----------------------------------------
	bool getTrigger(int value);

	//----------------------------------------
	//! @brief ���s�[�g��Ԏ擾�֐�
	//! @details
	//! @param value ���s�[�g��Ԃ��m�F�������L�[�{�[�h�{�^��ID
	//! @retval bool ������Ă����莞�Ԃ��̂܂܂̂Ƃ�true
	//----------------------------------------
	bool getRepeat(int value);

	//----------------------------------------
	//! @brief �����|�X��Ԏ擾�֐�
	//! @details
	//! @param value �����|�X��Ԃ��m�F�������L�[�{�[�h�{�^��ID
	//! @retval bool �������u��true
	//----------------------------------------
	bool getRelease(int value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param hInstance �C���X�^���X�n���h��
	//! @param hWnd      �E�B���h�E�n���h��
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

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

private:
	//----------------------------------------
	//! @brief DirectInput�������֐�
	//! @details
	//! @param hInstance �C���X�^���X�n���h��
	//! @param hWnd      �E�B���h�E�n���h��
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT InitDirectInput(HINSTANCE hInstance, HWND hWnd);
};



#endif