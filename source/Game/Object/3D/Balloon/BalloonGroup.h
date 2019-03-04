//================================================================================
//!	@file	 BalloonGroup.h
//!	@brief	 風船群Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_BALLOON_GROUP_H_
#define _BALLOON_GROUP_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// クラス定義
//****************************************
class Balloon;



//************************************************************														   
//! @brief   風船群Class
//!
//! @details 風船の集合Class
//************************************************************
class BalloonGroup : public GameObjectNull
{
//====================
// 定数
//====================
public:
	static const int MAX_BALLOON_NUM = 10;		//!< 最大風船数
	static const int BALLOON_LINE_NUM;			//!< 風船の線の数


//====================
// 変数
//====================
private:
	ReferenceList<BalloonGroup> reference_list_;	//!< 参照リスト
	std::vector<Balloon*> balloons_;				//!< 風船群
	int end_index_;									//!< 終端インデックス
	

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 参照リスト取得関数
	//! @details
	//! @param void なし
	//! @retval ReferenceList<BalloonGroup>* 参照リスト
	//----------------------------------------
	ReferenceList<BalloonGroup>* getpReferenceList();

	//----------------------------------------
	//! @brief 風船数取得関数
	//! @details
	//! @param void なし
	//! @retval int 風船数
	//----------------------------------------
	int getBalloonNum();

	//----------------------------------------
	//! @brief 風船の残り数取得関数
	//! @details
	//! @param void なし
	//! @retval int 風船数
	//----------------------------------------
	int getRemainingBalloonNum();

	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D 座標
	//----------------------------------------
	Vector3D getPosition();

	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vector3D value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param balloon_num 風船数
	//! @param position    座標
	//! @retval void なし
	//----------------------------------------
	void Init(unsigned balloon_num, Vector3D position);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 拘束解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseConstraint();

	//----------------------------------------
	//! @brief 速度追加関数
	//! @details
	//! @param velocity 速度
	//! @retval void なし
	//----------------------------------------
	void AddVelocity(Vector3D velocity);

	//----------------------------------------
	//! @brief 加速度追加関数
	//! @details
	//! @param acceleration 加速度
	//! @retval void なし
	//----------------------------------------
	void AddAcceleration(Vector3D acceleration);

	//----------------------------------------
	//! @brief 破裂関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Rupture();

private:
};



#endif