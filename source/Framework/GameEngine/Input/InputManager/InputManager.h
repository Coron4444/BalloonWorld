//================================================================================
//!	@file	 InputManager.h
//!	@brief	 インプットマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/03
//================================================================================
#ifndef	_INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include "../Controller.h"
#include "../Keyboard.h"



//************************************************************														   
//! @brief   インプットマネージャClass(Singleton)
//!
//! @details インプットマネージャClass(Singleton)
//************************************************************
class InputManager
{
//====================
// static変数
//====================
private:
	static InputManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval InputManager* インスタンス
	//----------------------------------------
	static InputManager* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();


//====================
// 変数
//====================
private:
	Controller* controller_;	//!< コントローラー
	Keyboard* keyboard_;		//!< キーボード


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief コントローラー取得関数
	//! @details
	//! @param void なし
	//! @retval Controller* コントローラー
	//----------------------------------------
	Controller* getpController();

	//----------------------------------------
	//! @brief キーボード取得関数
	//! @details
	//! @param void なし
	//! @retval Keyboard* キーボード
	//----------------------------------------
	Keyboard* getpKeyboard();


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	InputManager();

public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param hInstance インスタンスハンドル
	//! @param hWnd      ウィンドウハンドル
	//! @retval void なし
	//----------------------------------------
	void Init(HINSTANCE hInstance, HWND hWnd);

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


//====================
// 消去済み関数
//====================
private:
	InputManager(const InputManager& class_name) = delete;
	InputManager& operator = (const InputManager& class_name) = delete;
};



#endif
