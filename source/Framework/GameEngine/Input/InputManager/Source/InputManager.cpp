//================================================================================
//!	@file	 InputManager.h
//!	@brief	 �C���v�b�g�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/03
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../InputManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// static�ϐ���`
//****************************************
InputManager* InputManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
InputManager* InputManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new InputManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void InputManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
Controller* InputManager::getpController()
{
	return controller_;
}



Keyboard* InputManager::getpKeyboard()
{
	return keyboard_;
}



//****************************************
// �֐���`
//****************************************
InputManager::InputManager()
{
}



void InputManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	controller_ = new Controller();

	keyboard_ = new Keyboard();
	keyboard_->Init(hInstance, hWnd);
}



void InputManager::Uninit()
{
	SafeRelease::Normal(&controller_);
	SafeRelease::PlusUninit(&keyboard_);
}



void InputManager::Update()
{
	controller_->Update();
	keyboard_->Update();
}