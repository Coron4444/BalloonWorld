//================================================================================
//!	@file	 Controller.h
//!	@brief	 コントローラーClass
//! @details 
//!	@author  Kai Araki									@date 2017/09/24
//================================================================================
#ifndef	_CONTROLLER_H_
#define _CONTROLLER_H_



//****************************************
// インクルード文
//****************************************
#include <Windows.h>
#include <XInput.h>



//************************************************************														   
//! @brief   コントローラーClass
//!
//! @details コントローラーの入力Class
//************************************************************
class Controller
{
//====================
// クラス定義
//====================
public:
	//****************************************											   
	//! @brief   XInputコントローラーClass
	//!
	//! @details XInputコントローラー1つ分の状態を持つClass
	//****************************************
	class XInputController
	{
	//====================
	// 変数
	//====================
	private:
		XINPUT_STATE state_;				//!< ステート
		XINPUT_STATE old_state_;			//!< 1フレーム前のステート
		DWORD connection_message_;			//!< 接続メッセージ

	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief ステート取得関数
		//! @details
		//! @param void なし
		//! @retval XINPUT_STATE* ステート
		//----------------------------------------
		XINPUT_STATE* getpState();

		//----------------------------------------
		//! @brief 1フレーム前のステート取得関数
		//! @details
		//! @param void なし
		//! @retval XINPUT_STATE* 1フレーム前のステート
		//----------------------------------------
		XINPUT_STATE* getpOldState();

		//----------------------------------------
		//! @brief 接続メッセージ取得関数
		//! @details
		//! @param void なし
		//! @retval DWORD* 接続メッセージ
		//----------------------------------------
		DWORD* getpConnectionMessage();
	};


//====================
// 列挙型定義
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
// 定数
//====================
private:
	static const int STICK_TRIGGER_SENSITIVITY;		//!< スティックトリガー感度
	static const int STICK_HOLD_SENSITIVITY;		//!< スティックホールド感度
	static const int TRIGGER_BUTTON_SENSITIVITY;	//!< トリガーボタン感度


//====================
// 変数
//====================
private:
	XInputController controller_[(int)Number::MAX];		//!< XInputコントローラー


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ホールド状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 押されていればtrue
	//----------------------------------------
	bool getHold(int controller_index, int value);

	//----------------------------------------
	//! @brief トリガー状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 押した瞬間はtrue
	//----------------------------------------
	bool getTrigger(int controller_index, int value);

	//----------------------------------------
	//! @brief リリ－ス状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 離した瞬間true
	//----------------------------------------
	bool getRelease(int controller_index, int value);

	//----------------------------------------
	//! @brief Lスティックのホールド状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したい方向
	//! @retval bool 押されていればtrue
	//----------------------------------------
	bool getHoldLStick(int controller_index, Direction value);

	//----------------------------------------
	//! @brief Lスティックのトリガー状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したい方向
	//! @retval bool 押した瞬間はtrue
	//----------------------------------------
	bool getTriggerLStick(int controller_index, Direction value);

	//----------------------------------------
	//! @brief トリガーボタンのホールド状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 押されていればtrue
	//----------------------------------------
	bool getHoldTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief トリガーボタンのトリガー状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 押した瞬間はtrue
	//----------------------------------------
	bool getTriggerTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief トリガーボタンのリリ－ス状態取得関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @param value            判定したいボタン
	//! @retval bool 離した瞬間true
	//----------------------------------------
	bool getReleaseTriggerButton(int controller_index, TriggerButton value);

	//----------------------------------------
	//! @brief コントローラー数取得関数
	//! @details
	//! @param void なし
	//! @retval int コントローラー数
	//----------------------------------------
	int getControllerNum();

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief コントローラー接続確認関数
	//! @details
	//! @param controller_index コントローラーインデックス
	//! @retval bool 接続されていればtrue
	//----------------------------------------
	bool IsConnection(int controller_index);
};



#endif