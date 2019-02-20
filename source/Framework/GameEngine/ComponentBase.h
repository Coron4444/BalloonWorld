//================================================================================
//!	@file	 ComponentBase.h
//!	@brief	 コンポーネントBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// インクルード文
//****************************************
#ifdef _DEBUG
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
#endif

#include "GameObject/GameObjectBase.h"



//************************************************************														   
//! @brief   コンポーネントBaseClass
//!
//! @details コンポーネントのBaseClass
//************************************************************
class ComponentBase
{
//====================
// 変数
//====================
private:
	GameObjectBase* game_object_;	//!< ゲームオブジェクト
	bool is_enable_ = true;			//!< 有効フラグ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ゲームオブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval GameObjectBase* ゲームオブジェクト
	//----------------------------------------
	GameObjectBase* getpGameObject();
	
	//----------------------------------------
	//! @brief ゲームオブジェクト設定関数
	//! @details
	//! @param value ゲームオブジェクト
	//! @retval void なし
	//----------------------------------------
	void setGameObject(GameObjectBase* value);

	//----------------------------------------
	//! @brief 有効フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 有効フラグ
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief 有効フラグ取得関数
	//! @details
	//! @param value 有効フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsEnable(bool value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~ComponentBase() = 0;

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset() = 0;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() = 0;
};



#endif