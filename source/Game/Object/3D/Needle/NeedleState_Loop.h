//================================================================================
//!	@file	 NeedleState_Loop.h
//!	@brief	 棘ステートループClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_NEEDLE_STATE_LOOP_H_
#define _NEEDLE_STATE_LOOP_H_



//****************************************
// インクルード文
//****************************************
#include "Needle.h"



//************************************************************														   
//! @brief   棘ステートループClass
//!
//! @details 棘ステートのループClass
//************************************************************
class NeedleState_Loop : public Needle::State
{
//====================
// 定数
//====================
private:
	static const Vec3 CENTER_POSITION;			//!< 中心からの座標
	static const float ROTATION_CENTER_SPEED;	//!< 中心の回転速度
	static const float ROTATION_SPEED;			//!< 回転速度


//====================
// 変数
//====================
private:
	Transform rotation_transform_;	//!<  回転用変形


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
};



#endif