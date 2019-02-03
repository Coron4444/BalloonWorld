//================================================================================
//!	@file	 Controller.h
//!	@brief	 コントローラーClass
//! @details 
//!	@author  Kai Araki									@date 2017/09/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Controller.h"



//****************************************
// 定数定義
//****************************************
const int Controller::STICK_TRIGGER_SENSITIVITY = 30000;
const int Controller::STICK_HOLD_SENSITIVITY = 100;
const int Controller::TRIGGER_BUTTON_SENSITIVITY = 5;



//****************************************
// プロパティ定義
//****************************************
XINPUT_STATE* Controller::XInputController::getpState()
{
	return &state_;
}



XINPUT_STATE* Controller::XInputController::getpOldState()
{
	return &old_state_;
}



DWORD* Controller::XInputController::getpConnectionMessage()
{
	return &connection_message_;
}



bool Controller::getHold(int controller_index, int value)
{
	if (controller_[controller_index].getpState()->Gamepad.wButtons & value) return true;
	return false;
}



bool Controller::getTrigger(int controller_index, int value)
{
	if (!(controller_[controller_index].getpState()->Gamepad.wButtons & value)) return false;
	if (controller_[controller_index].getpOldState()->Gamepad.wButtons & value) return false;
	return true;
}



bool Controller::getRelease(int controller_index, int value)
{
	if (!(controller_[controller_index].getpOldState()->Gamepad.wButtons & value)) return false;
	if (controller_[controller_index].getpState()->Gamepad.wButtons & value) return false;
	return true;
}



bool Controller::getHoldLStick(int controller_index, Controller::Direction value)
{
	switch (value)
	{
		case Controller::Direction::UP:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLY < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::DOWN:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLY > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::LEFT:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLX > -STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::RIGHT:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLX < STICK_HOLD_SENSITIVITY) return false;
			return true;
		}
	}
	return false;
}



bool Controller::getTriggerLStick(int controller_index, Controller::Direction value)
{
	switch (value)
	{
		case Controller::Direction::UP:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLY < STICK_TRIGGER_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.sThumbLY >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::DOWN:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLY > -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.sThumbLY <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::LEFT:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLX > -STICK_TRIGGER_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.sThumbLX <= -STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
		case Controller::Direction::RIGHT:
		{
			if (controller_[controller_index].getpState()->Gamepad.sThumbLX < STICK_TRIGGER_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.sThumbLX >= STICK_TRIGGER_SENSITIVITY) return false;
			return true;
		}
	}
	return false;
}



bool Controller::getHoldTriggerButton(int controller_index, 
									  Controller::TriggerButton value)
{
	switch (value)
	{
		case Controller::TriggerButton::R2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bRightTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.bRightTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
		case Controller::TriggerButton::L2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bLeftTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.bLeftTrigger >= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}

	return false;
}



bool Controller::getTriggerTriggerButton(int controller_index, 
										 Controller::TriggerButton value)
{
	switch (value)
	{
		case Controller::TriggerButton::R2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bRightTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
		case Controller::TriggerButton::L2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bLeftTrigger < TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}
	return false;
}



bool Controller::getReleaseTriggerButton(int controller_index, 
										 Controller::TriggerButton value)
{
	switch (value)
	{
		case Controller::TriggerButton::R2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bRightTrigger > TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.bRightTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
		case Controller::TriggerButton::L2:
		{
			if (controller_[controller_index].getpState()->Gamepad.bLeftTrigger > TRIGGER_BUTTON_SENSITIVITY) return false;
			if (controller_[controller_index].getpOldState()->Gamepad.bLeftTrigger <= TRIGGER_BUTTON_SENSITIVITY) return false;
			return true;
		}
	}
	return false;
}



int Controller::getControllerNum()
{
	int num = 0;
	for (int i = 0; i < (int)Controller::Number::MAX; i++)
	{
		if (*controller_[i].getpConnectionMessage() != ERROR_SUCCESS) continue;
		num++;
	}
	return num;
}



//****************************************
// 関数定義
//****************************************
void Controller::Update()
{
	for (int i = 0; i < (int)Controller::Number::MAX; i++)
	{
		*controller_[i].getpOldState() = *controller_[i].getpState();
		*controller_[i].getpConnectionMessage() = XInputGetState(i, controller_[i].getpState());
	}
}



bool Controller::IsConnection(int controller_index)
{
	if (*controller_[controller_index].getpConnectionMessage()
		!= ERROR_DEVICE_NOT_CONNECTED) return true;
	return false;
}