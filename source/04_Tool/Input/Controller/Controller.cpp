//================================================================================
//
//    �R���g���[���[
//    Author : Araki Kai                                �쐬�� : 2017/09/24
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "Controller.h"



//**********************************************************************
//
// �萔��`
//
//**********************************************************************

// �X�e�B�b�N���x(�g���K�[)
const int STICK_TRIGGER_SENSITIVITY  = 30000;
const int STICK_HOLD_SENSITIVITY     = 100;
const int TRIGGER_BUTTON_SENSITIVITY = 5;



//**********************************************************************
//
// �O���[�o���ϐ�
//
//**********************************************************************

namespace
{
	XInputController controller[CONTOROLLER_NUM_MAX];
}






//**********************************************************************
//
// �v���g�^�C�v�錾
//
//**********************************************************************

//================================================================================
//
// [ �R���g���[���[�̒l�ݒ�֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��R���g���[���[�̒l��ݒ肷��
//
//================================================================================

void SetController()
{
	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		controller[i].oldState = controller[i].state;

		controller[i].connectionMessage = XInputGetState(i, &controller[i].state);

	}
}



//================================================================================
//
// [ �R���g���[���[�̃{�^������֐�( HOLD ) ]
//
// � ���� �
//
// �controllerNum : �R���g���[���[�ԍ�
// �buttonNum     : ���肵�����{�^��
//
// � �߂�l �
//
// �bool�^ : �������ςȂ����ǂ�����Ԃ�
//
//�y �ڍ� �z
//
// ������œn���ꂽ�R���g���[���[�̃{�^����HOLD��Ԃ��𔻒肷��
//
//================================================================================

bool InputHoldController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].state.Gamepad.wButtons & buttonNum)
	{
		return true;
	}

	return false;
}



//================================================================================
//
// [ �R���g���[���[�̃{�^������֐�( TRIG ) ]
//
// � ���� �
//
// �controllerNum : �R���g���[���[�ԍ�
// �buttonNum     : ���肵�����{�^��
//
// � �߂�l �
//
// �bool�^ : �������ςȂ����ǂ�����Ԃ�
//
//�y �ڍ� �z
//
// ������œn���ꂽ�R���g���[���[�̃{�^����TRIG��Ԃ��𔻒肷��
//
//================================================================================

bool InputTriggerController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].state.Gamepad.wButtons & buttonNum)
	{
		if (controller[controllerNum].oldState.Gamepad.wButtons & buttonNum)
		{
			return false;
		}

		return true;
	}

	return false;
}



//================================================================================
//
// [ �R���g���[���[�̃{�^������֐�( RELEASE ) ]
//
// � ���� �
//
// �controllerNum : �R���g���[���[�ԍ�
// �buttonNum     : ���肵�����{�^��
//
// � �߂�l �
//
// �bool�^ : �������ςȂ����ǂ�����Ԃ�
//
//�y �ڍ� �z
//
// ������œn���ꂽ�R���g���[���[�̃{�^����RELEASE��Ԃ��𔻒肷��
//
//================================================================================

bool InputReleaseController(int controllerNum, int buttonNum)
{
	if (controller[controllerNum].oldState.Gamepad.wButtons & buttonNum)
	{
		if (!(controller[controllerNum].state.Gamepad.wButtons & buttonNum))
		{
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ �R���g���[���[��L�X�e�B�b�N����֐�(TRIG ) ]
//
// � ���� �
//
// �controllerNum : �R���g���[���[�ԍ�
//
// � �߂�l �
//
// �bool�^ : �����萔�𒴂����甽������
//
//�y �ڍ� �z
//
// ������œn���ꂽ�R���g���[���[��L�X�e�B�b�N��TRIG���𔻒肷��
//
//================================================================================

bool InputLStickTriggerController(int controllerNum, int direction)
{
	switch (direction)
	{
		case STICK_UP :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY      <  STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[ controllerNum ].oldState.Gamepad.sThumbLY >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}	
		case STICK_DOWN :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY    >  -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLY <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case STICK_LEFT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX    >  -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLX <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case STICK_RIGHT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX    <  STICK_TRIGGER_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.sThumbLX >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ �R���g���[���[��L�X�e�B�b�N����֐�(HOLD) ]
//
//================================================================================

bool InputLStickHoldController(int controllerNum, int direction)
{
	switch (direction)
	{
		case STICK_UP :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}	
		case STICK_DOWN :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLY > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case STICK_LEFT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case STICK_RIGHT :
		{
			if (controller[controllerNum].state.Gamepad.sThumbLX < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [�R���g���[���[��R2L2����֐�(TRIG)]
//
//================================================================================

bool InputR2L2TriggerController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger    <  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bRightTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger    <  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bLeftTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [�R���g���[���[��R2L2����֐�(HOLD)]
//
//================================================================================

bool InputR2L2HoldController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [�R���g���[���[��R2L2����֐�(RELEASE)]
//
//================================================================================

bool InputR2L2ReleaseController(int controllerNum, int direction)
{
	switch (direction)
	{
		case TRIGGER_BUTTON_R2 :
		{
			if (controller[controllerNum].state.Gamepad.bRightTrigger    >  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bRightTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}	
		case TRIGGER_BUTTON_L2 :
		{
			if (controller[controllerNum].state.Gamepad.bLeftTrigger    >  TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller[controllerNum].oldState.Gamepad.bLeftTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



//================================================================================
//
// [ �R���g���[���[���q�����Ă��邩�̔���֐� ]
//
// � ���� �
//
// �controllerNum : �R���g���[���[�ԍ�
//
// � �߂�l �
//
// �bool�^ : �ڑ�����Ă����true��Ԃ�
//
//�y �ڍ� �z
//
// ��ڑ�����Ă����true��Ԃ�
//
//================================================================================

bool CheckController(int controllerNum)
{
	if (controller[controllerNum].connectionMessage == ERROR_DEVICE_NOT_CONNECTED)
	{
		return false;
	}

	return true;
}



//================================================================================
//
// [ �ڑ�����Ă���R���g���[���[���̎擾�֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// �int�^ : �ڑ�����Ă���R���g���[���[�̐���Ԃ�
//
//�y �ڍ� �z
//
// ��ڑ�����Ă���R���g���[���[����Ԃ�
//
//================================================================================

int GetControllerNum()
{
	int tempNum = 0;

	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		if (controller[i].connectionMessage == ERROR_SUCCESS)
		{
			tempNum++;
		}
	}

	return tempNum;
}



//================================================================================
//
// [ 1��ł��R���g���[���[���ڑ�����Ă��邩�t���O�֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// �int�^ : 1��ł��R���g���[���[���ڑ�����Ă����1��Ԃ�
//
//�y �ڍ� �z
//
// �1��ł��R���g���[���[���ڑ�����Ă����1��Ԃ�
//
//================================================================================

int GetControllerConnect()
{
	for (int i = 0; i < CONTOROLLER_NUM_MAX; i++)
	{
		if (controller[i].connectionMessage == ERROR_SUCCESS)
		{
			return CONNECT_ONE;
		}
	}

	return 0;
}