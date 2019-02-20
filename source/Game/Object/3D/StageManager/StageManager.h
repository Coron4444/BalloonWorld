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
// 変数
//====================
private:
	Camera* camera_ = nullptr;					//!< カメラ
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
	//! @brief プレイヤーカメラ設定関数
	//! @details
	//! @param *value カメラ
	//! @retval void なし
	//----------------------------------------
	void setPlayerCamera(Camera* value);

	//----------------------------------------
	//! @brief プレイヤー取得関数
	//! @details
	//! @param 
	//! @retval void なし
	//----------------------------------------
	Player* getpPlayer();


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