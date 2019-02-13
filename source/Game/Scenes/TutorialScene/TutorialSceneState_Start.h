//================================================================================
//!	@file	 TutorialSceneState_Start.h
//!	@brief	 チュートリアルシーンステート(スタート)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TUTORIAL_SCENE_STATE_START_H_
#define _TUTORIAL_SCENE_STATE_START_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Scene/SceneNull.h>



//****************************************
// クラス宣言
//****************************************
class TutorialScene;



//************************************************************														   
//! @brief   チュートリアルシーンステート(スタート)Class
//!
//! @details チュートリアルシーンのステート(スタート)Class
//! @details 最初の状態を表す
//************************************************************
class TutorialSceneState_Start : public SceneNull::StateNull
{
//====================
// 変数
//====================
private:
	TutorialScene* tutorial_scene_ = nullptr;		//!< チュートリアルシーン
	

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;
};



#endif