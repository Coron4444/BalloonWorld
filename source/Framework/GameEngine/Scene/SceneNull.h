//================================================================================
//!	@file	 SceneNull.h
//!	@brief	 シーン空白Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_SCENE_NULL_H_
#define _SCENE_NULL_H_



//****************************************
// インクルード文
//****************************************
#include "SceneBase.h"



//************************************************************														   
//! @brief   シーン空白Class
//!
//! @details シーンの空白Class
//************************************************************
class SceneNull : public SceneBase
{
//====================
// クラス
//====================
public:
	//****************************************														   
	//! @brief   シーンステート空白Class
	//!
	//! @details シーンステートの空白Class
	//****************************************
	class StateNull : public SceneBase::StateBase
	{
	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief デストラクタ
		//! @details
		//! @param void なし
		//----------------------------------------
		virtual ~StateNull();

		//----------------------------------------
		//! @brief 初期化関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Init();

		//----------------------------------------
		//! @brief 終了関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Uninit();

		//----------------------------------------
		//! @brief 更新関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Update();

		//----------------------------------------
		//! @brief ポーズ入口関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void PauseEntrance();

		//----------------------------------------
		//! @brief ポーズ出口関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void PauseExit();
	};


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param *state 最初のステート
	//----------------------------------------
	SceneNull(StateBase* state);

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~SceneNull();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update();

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset();
};



#endif