//================================================================================
//!	@file	 Keyboard.h
//!	@brief	 �L�[�{�[�hClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Keyboard.h"



//****************************************
// �萔��`
//****************************************
const DWORD Keyboard::INPUT_VERSION = 0x0800;
const int Keyboard::LIMIT_COUNT_REPEAT = 20;



//****************************************
// �v���p�e�B��`
//****************************************
bool Keyboard::getHold(int value)
{
	return (key_state_[value] & 0x80) ? true : false;
}



bool Keyboard::getTrigger(int value)
{
	return (key_state_trigger_[value] & 0x80) ? true : false;
}



bool Keyboard::getRepeat(int value)
{
	return (key_state_repeat_[value] & 0x80) ? true : false;
}



bool Keyboard::getRelease(int value)
{
	return (key_state_release_[value] & 0x80) ? true : false;
}



//****************************************
// �֐���`
//****************************************
HRESULT Keyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput������
	if (FAILED(InitDirectInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput���������s", "Error", MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�쐬
	if (FAILED(direct_input_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���������s", "Error", MB_OK);
		return E_FAIL;
	}


	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(keyboard_->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g�̐ݒ莸�s", "Error", MB_OK);
		return E_FAIL;
	}


	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j�d�v!!
	if (FAILED(keyboard_->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h�̐ݒ莸�s", "Error", MB_OK);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	keyboard_->Acquire();

	return S_OK;
}



void Keyboard::Uninit()
{
	if (keyboard_ != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		keyboard_->Unacquire();

		keyboard_->Release();
		keyboard_ = NULL;
	}

	// ���͏����̏I������
	SafeRelease::PlusRelease(&direct_input_);
}



void Keyboard::Update()
{
	BYTE temp_key_state[MAX_KEY_NUM];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(keyboard_->GetDeviceState(sizeof(temp_key_state), temp_key_state)))
	{
		for (int i = 0; i < MAX_KEY_NUM; i++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			key_state_trigger_[i] = (key_state_[i] ^ temp_key_state[i]) & temp_key_state[i];
			key_state_release_[i] = (key_state_[i] ^ temp_key_state[i]) & key_state_[i];


			// �L�[���s�[�g���𐶐�
			if (temp_key_state[i])
			{
				if (repeat_counter_[i] < LIMIT_COUNT_REPEAT)
				{
					repeat_counter_[i]++;
					if (repeat_counter_[i] == 1
						|| repeat_counter_[i] >= LIMIT_COUNT_REPEAT)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
						key_state_repeat_[i] = temp_key_state[i];
					}
					else
					{
						key_state_repeat_[i] = 0;
					}
				}
			}
			else
			{
				repeat_counter_[i] = 0;
				key_state_repeat_[i] = 0;
			}

			// �L�[�v���X����ۑ�
			key_state_[i] = temp_key_state[i];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		keyboard_->Acquire();
	}
}



HRESULT Keyboard::InitDirectInput(HINSTANCE hInstance, HWND hWnd)
{
	hWnd = hWnd;
	if (direct_input_ == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, Keyboard::INPUT_VERSION,
									  IID_IDirectInput8, (void**)&direct_input_, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}