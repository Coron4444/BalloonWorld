//================================================================================
//!	@file	 GameScene.h
//!	@brief	 ゲームシーンClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Scene/SceneNull.h>



//****************************************
// クラス宣言
//****************************************
class Pause;
class StageManager;
class Score;
class Time;
class BalloonNum;



//************************************************************														   
//! @brief   ゲームシーンClass
//!
//! @details ゲームシーンを管理するClass
//! @details ゲームシーン特有の共有データを持っている
//************************************************************
class GameScene : public SceneNull
{
//====================
// 変数
//====================
public:
	enum class State
	{
		NONE = -1,
		START,
		GAME,
		PAUSE,
		END,
		MAX
	};


//====================
// 変数
//====================
private:
	Pause* pause_ = nullptr;					//!< ポーズ
	StageManager* stage_manager_ = nullptr;		//!< ステージマネージャ
	Score* score_ = nullptr;					//!< スコア					
	Time* time_ = nullptr;						//!< 時間
	BalloonNum* balloon_num_ = nullptr;			//!< 風船数


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ステージマネージャ取得関数
	//! @details
	//! @param void なし
	//! @retval StageManager* ステージマネージャ
	//----------------------------------------
	StageManager* getpStageManager();

	//----------------------------------------
	//! @brief ステージマネージャ設定関数
	//! @details
	//! @param void なし
	//! @retval StageManager* ステージマネージャ
	//----------------------------------------
	void setStageManager(StageManager* value);

	//----------------------------------------
	//! @brief スコア取得関数
	//! @details
	//! @param void なし
	//! @retval Score* スコア
	//----------------------------------------
	Score* getpScore();

	//----------------------------------------
	//! @brief 時間取得関数
	//! @details
	//! @param void なし
	//! @retval Time* 時間
	//----------------------------------------
	Time* getpTime();

	//----------------------------------------
	//! @brief 風船数取得関数
	//! @details
	//! @param void なし
	//! @retval BalloonNum* 風船数
	//----------------------------------------
	BalloonNum* getpBalloonNum();

	//----------------------------------------
	//! @brief 全UI設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void setAllUI();

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param *value ステート
	//----------------------------------------
	GameScene(StateBase* state);

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
	virtual void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();
};



#endif