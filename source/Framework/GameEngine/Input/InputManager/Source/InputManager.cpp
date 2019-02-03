//================================================================================
//!	@file	 InputManager.h
//!	@brief	 インプットマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/03
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../InputManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// static変数定義
//****************************************
InputManager* InputManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
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
// static関数定義
//****************************************
void InputManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
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
// 関数定義
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