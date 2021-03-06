//================================================================================
//!	@file	 TitleScene.h
//!	@brief	 タイトルシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TITLE_SCENE_H_
#define _TITLE_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Scene/SceneNull.h>



//************************************************************														   
//! @brief   タイトルシーンClass
//!
//! @details タイトルシーンを管理するClass
//! @details タイトルシーン特有の共有データを持っている
//************************************************************
class TitleScene : public SceneNull
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param *state 最初のステート
	//----------------------------------------
	TitleScene(StateBase* state);

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();
};



#endif