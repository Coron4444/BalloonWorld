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
#include <vector>

#include <GameEngine/GameObject/GameObjectNull.h>
#include <Tool/ReferenceList.h>



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
	//! @retval unsigned 風船数
	//----------------------------------------
	unsigned getBalloonNum();

	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vec3 座標
	//----------------------------------------
	Vec3 getPosition();

	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vec3 value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param balloon_num 風船数
	//! @retval void なし
	//----------------------------------------
	void Init(unsigned balloon_num);

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
	void AddVelocity(Vec3 velocity);

	//----------------------------------------
	//! @brief 加速度追加関数
	//! @details
	//! @param acceleration 加速度
	//! @retval void なし
	//----------------------------------------
	void AddAcceleration(Vec3 acceleration);

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