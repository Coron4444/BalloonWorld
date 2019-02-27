//================================================================================
//!	@file	 Keyboard.h
//!	@brief	 キーボードClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef _KYEBOARD_H_
#define _KYEBOARD_H_



//****************************************
// インクルード文
//****************************************
#include < dinput.h >



//************************************************************														   
//! @brief   キーボードClass
//!
//! @details キーボードの入力Class
//************************************************************
class Keyboard
{
//====================
// 定数
//====================
private:
	static const DWORD INPUT_VERSION;			//!< ダイレクトインプットバージョン
	static const int MAX_KEY_NUM = 256;			//!< キーの最大数
	static const int LIMIT_COUNT_REPEAT;		//!< リピートカウントリミット


//====================
// 変数
//====================
private:
	LPDIRECTINPUT8 direct_input_ = nullptr;		//!< DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8 keyboard_ = nullptr;	//!< 入力デバイス(キーボード)
	BYTE key_state_[MAX_KEY_NUM];				//!< キーボードの入力情報
	BYTE key_state_trigger_[MAX_KEY_NUM];		//!< キーボードのトリガー情報
	BYTE key_state_repeat_[MAX_KEY_NUM];		//!< キーボードのリピート情報
	BYTE key_state_release_[MAX_KEY_NUM];		//!< キーボードのリリース情報
	int repeat_counter_[MAX_KEY_NUM];			//!< リピートカウンター


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ホールド状態取得関数
	//! @details
	//! @param value ホールド状態を確認したいキーボードボタンID
	//! @retval bool 押されていればtrue
	//----------------------------------------
	bool getHold(int value);

	//----------------------------------------
	//! @brief トリガー状態取得関数
	//! @details
	//! @param value トリガー状態を確認したいキーボードボタンID
	//! @retval bool 押した瞬間はtrue
	//----------------------------------------
	bool getTrigger(int value);

	//----------------------------------------
	//! @brief リピート状態取得関数
	//! @details
	//! @param value リピート状態を確認したいキーボードボタンID
	//! @retval bool 押されてから一定時間そのままのときtrue
	//----------------------------------------
	bool getRepeat(int value);

	//----------------------------------------
	//! @brief リリ－ス状態取得関数
	//! @details
	//! @param value リリ－ス状態を確認したいキーボードボタンID
	//! @retval bool 離した瞬間true
	//----------------------------------------
	bool getRelease(int value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param hInstance インスタンスハンドル
	//! @param hWnd      ウィンドウハンドル
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

private:
	//----------------------------------------
	//! @brief DirectInput初期化関数
	//! @details
	//! @param hInstance インスタンスハンドル
	//! @param hWnd      ウィンドウハンドル
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT InitDirectInput(HINSTANCE hInstance, HWND hWnd);
};



#endif