//================================================================================
//!	@file	 Scaffold.h
//!	@brief	 足場Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_SCAFFOLD_H_
#define _SCAFFOLD_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   足場Class
//!
//! @details 足場のClass
//************************************************************
class Scaffold : public GameObjectNull
{
//====================
// 定数
//====================
private:
	static const Vector3D SCALE;				//!< 拡縮


//====================
// 変数
//====================
private:
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};		//!< 色
	int score_ = 0;


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vector3D value);

	//----------------------------------------
	//! @brief 拡縮設定関数
	//! @details
	//! @param value 拡縮
	//! @retval void なし
	//----------------------------------------
	void setScale(Vector3D value);

	//----------------------------------------
	//! @brief 色取得関数
	//! @details
	//! @param void なし
	//! @retval XColor4* 色
	//----------------------------------------
	XColor4* getpColor();

	//----------------------------------------
	//! @brief 色設定関数
	//! @details
	//! @param value 色
	//! @retval void なし
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief スコア取得関数
	//! @details
	//! @param value スコア
	//! @retval void なし
	//----------------------------------------
	int getScore();

	//----------------------------------------
	//! @brief スコア設定関数
	//! @details
	//! @param value スコア
	//! @retval void なし
	//----------------------------------------
	void setScore(int value);



//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw      描画基底クラス
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;
};



#endif