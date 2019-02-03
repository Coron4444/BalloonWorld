//================================================================================
//!	@file	 Controller.h
//!	@brief	 �R���g���[���[Class
//! @details 
//!	@author  Kai Araki									@date 2017/09/24
//================================================================================
#ifndef	_CONTROLLER_H_
#define _CONTROLLER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>
#include <XInput.h>



//************************************************************														   
//! @brief   �R���g���[���[Class
//!
//! @details �R���g���[���[�̓���Class
//************************************************************
class Controller
{
//====================
// �N���X��`
//====================
public:
	//****************************************											   
	//! @brief   XInput�R���g���[���[Class
	//!
	//! @details XInput�R���g���[���[1���̏�Ԃ�����Class
	//****************************************
	class XInputController
	{
	//====================
	// �ϐ�
	//====================
	private:
		XINPUT_STATE state_;				//!< �X�e�[�g
		XINPUT_STATE old_state_;			//!< 1�t���[���O�̃X�e�[�g
		DWORD connection_message_;			//!< �ڑ����b�Z�[�W

	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �X�e�[�g�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval XINPUT_STATE* �X�e�[�g
		//----------------------------------------
		XINPUT_STATE* getpState();

		//----------------------------------------
		//! @brief 1�t���[���O�̃X�e�[�g�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval XINPUT_STATE* 1�t���[���O�̃X�e�[�g
		//----------------------------------------
		XINPUT_STATE* getpOldState();

		//----------------------------------------
		//! @brief �ڑ����b�Z�[�W�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval DWORD* �ڑ����b�Z�[�W
		//----------------------------------------
		DWORD* getpConnectionMessage();
	};


//====================
// �񋓌^��`
//====================
public:
	enum class Number
	{
		NONE = -1,
		ONE,
		TWO,
		THREE,
		fOUR,
		MAX
	};

	enum class Direction
	{
		NONE = -1,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX
	};

	enum class TriggerButton
	{
		NONE = -1,
		R2,
		L2,
		MAX
	};


//====================
// �萔
//====================
private:
	static const int STICK_TRIGGER_SENSITIVITY;		//!< �X�e�B�b�N�g���K�[���x
	static const int STICK_HOLD_SENSITIVITY;		//!< �X�e�B�b�N�z�[���h���x
	static const int TRIGGER_BUTTON_SENSITIVITY;	//!< �g���K�[�{�^�����x


//====================
// �ϐ�
//====================
private:
	XInputController controller_[(int)Number::MAX];		//!< XInput�R���g���[���[


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �z�[���h��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool ������Ă����true
	//----------------------------------------
	bool getHold(int controller_index, int value);

	//----------------------------------------
	//! @brief �g���K�[��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool �������u�Ԃ�true
	//----------------------------------------
	bool getTrigger(int controller_index, int value);

	//----------------------------------------
	//! @brief �����|�X��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool �������u��true
	//----------------------------------------
	bool getRelease(int controller_index, int value);

	//----------------------------------------
	//! @brief L�X�e�B�b�N�̃z�[���h��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵��������
	//! @retval bool ������Ă����true
	//----------------------------------------
	bool getHoldLStick(int controller_index, Direction value);

	//----------------------------------------
	//! @brief L�X�e�B�b�N�̃g���K�[��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵��������
	//! @retval bool �������u�Ԃ�true
	//----------------------------------------
	bool getTriggerLStick(int controller_index, Direction value);

	//----------------------------------------
	//! @brief �g���K�[�{�^���̃z�[���h��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool ������Ă����true
	//----------------------------------------
	bool getHoldTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief �g���K�[�{�^���̃g���K�[��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool �������u�Ԃ�true
	//----------------------------------------
	bool getTriggerTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief �g���K�[�{�^���̃����|�X��Ԏ擾�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @param value            ���肵�����{�^��
	//! @retval bool �������u��true
	//----------------------------------------
	bool getReleaseTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief �R���g���[���[���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �R���g���[���[��
	//----------------------------------------
	int getControllerNum();

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �R���g���[���[�ڑ��m�F�֐�
	//! @details
	//! @param controller_index �R���g���[���[�C���f�b�N�X
	//! @retval bool �ڑ�����Ă����true
	//----------------------------------------
	bool IsConnection(int controller_index);
};



#endif