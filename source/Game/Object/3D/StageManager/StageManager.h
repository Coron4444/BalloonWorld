//================================================================================
//!	@file	 StageManager.h
//!	@brief	 ステージマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// クラス宣言
//****************************************
class BalloonGroup;
class Camera;
class Player;
class StartBlock;
class Scaffold;
class Needle;


//************************************************************														   
//! @brief   ステージマネージャClass
//!
//! @details ステージマネージャのClass
//************************************************************
class StageManager : public GameObjectNull
{
//====================
// 定数
//====================
private:
	static const int MAX_TIME;		//!< 最大時間
	static const int BONUS_SCORE;		//!< ボーナススコア
	static const int BONUS_SCORE_RAITO;	//!< ボーナススコア比率


//====================
// 変数
//====================
private:
	bool is_enable_ = false;					//!< 有効フラグ
	bool is_ground_ = false;					//!< 着地フラグ
	int score_ = 0;								//!< スコア
	int time_ = 0;								//!< 時間
	BalloonGroup* balloon_group_ = nullptr;		//!< 風船群
	Player* player_ = nullptr;					//!< プレイヤー
	StartBlock* start_block_ = nullptr;			//!< スタートブロック
	Scaffold* scaffold_ = nullptr;				//!< 足場
	Needle* needle_ = nullptr;					//!< 棘


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 有効フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval value 有効フラグ
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief 有効フラグ設定関数
	//! @details
	//! @param value 有効フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsEnable(bool value);

	//----------------------------------------
	//! @brief スコア取得関数
	//! @details
	//! @param void なし
	//! @retval int スコア
	//----------------------------------------
	int getScore();

	//----------------------------------------
	//! @brief 時間取得関数
	//! @details
	//! @param void なし
	//! @retval int 時間
	//----------------------------------------
	int getTime();

	//----------------------------------------
	//! @brief 風船数取得関数
	//! @details
	//! @param void なし
	//! @retval int 風船数
	//----------------------------------------
	int getBalloonNum();

	//----------------------------------------
	//! @brief プレイヤーカメラ設定関数
	//! @details
	//! @param *value カメラ
	//! @retval void なし
	//----------------------------------------
	void setPlayerCamera(Camera* value);

	//----------------------------------------
	//! @brief プレイヤー取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	Player* getpPlayer();

	//----------------------------------------
	//! @brief 地面着地フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	bool getIsOnTheGround();


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
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief ステージ作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateStage();
};



#endif