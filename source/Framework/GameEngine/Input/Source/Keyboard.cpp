//================================================================================
//!	@file	 Keyboard.h
//!	@brief	 キーボードClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Keyboard.h"



//****************************************
// 定数定義
//****************************************
const DWORD Keyboard::INPUT_VERSION = 0x0800;
const int Keyboard::LIMIT_COUNT_REPEAT = 20;



//****************************************
// プロパティ定義
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
// 関数定義
//****************************************
HRESULT Keyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput初期化
	if (FAILED(InitDirectInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput初期化失敗", "Error", MB_OK);
		return E_FAIL;
	}

	// デバイス作成
	if (FAILED(direct_input_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL)))
	{
		MessageBox(hWnd, "キーボード初期化失敗", "Error", MB_OK);
		return E_FAIL;
	}


	// データフォーマットを設定
	if (FAILED(keyboard_->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットの設定失敗", "Error", MB_OK);
		return E_FAIL;
	}


	// 協調モードを設定（フォアグラウンド＆非排他モード）重要!!
	if (FAILED(keyboard_->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードの設定失敗", "Error", MB_OK);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	keyboard_->Acquire();

	return S_OK;
}



void Keyboard::Uninit()
{
	if (keyboard_ != NULL)
	{// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		keyboard_->Unacquire();

		keyboard_->Release();
		keyboard_ = NULL;
	}

	// 入力処理の終了処理
	SafeRelease::PlusRelease(&direct_input_);
}



void Keyboard::Update()
{
	BYTE temp_key_state[MAX_KEY_NUM];

	// デバイスからデータを取得
	if (SUCCEEDED(keyboard_->GetDeviceState(sizeof(temp_key_state), temp_key_state)))
	{
		for (int i = 0; i < MAX_KEY_NUM; i++)
		{
			// キートリガー・リリース情報を生成
			key_state_trigger_[i] = (key_state_[i] ^ temp_key_state[i]) & temp_key_state[i];
			key_state_release_[i] = (key_state_[i] ^ temp_key_state[i]) & key_state_[i];


			// キーリピート情報を生成
			if (temp_key_state[i])
			{
				if (repeat_counter_[i] < LIMIT_COUNT_REPEAT)
				{
					repeat_counter_[i]++;
					if (repeat_counter_[i] == 1
						|| repeat_counter_[i] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
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

			// キープレス情報を保存
			key_state_[i] = temp_key_state[i];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		keyboard_->Acquire();
	}
}



HRESULT Keyboard::InitDirectInput(HINSTANCE hInstance, HWND hWnd)
{
	hWnd = hWnd;
	if (direct_input_ == NULL)
	{
		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, Keyboard::INPUT_VERSION,
									  IID_IDirectInput8, (void**)&direct_input_, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}