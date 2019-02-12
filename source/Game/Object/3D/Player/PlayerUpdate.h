//================================================================================
//!	@file	 PlayerUpdate.h
//!	@brief	 プレイヤー更新Class
//! @details 
//!	@author  Kai Araki									@date 2019/03/27
//================================================================================
#ifndef	_PLAYER_UPDATE_H_
#define _PLAYER_UPDATE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Update/UpdateNull.h>



//****************************************
// クラス宣言
//****************************************
class Player;
class BulletPhysicsObject;



//************************************************************														   
//! @brief   プレイヤー更新Class
//!
//! @details プレイヤーの更新Class
//************************************************************
class PlayerUpdate : public UpdateNull
{
//====================
// 変数
//====================
private:
	static const float ACCELERATION;	//!< 加速度


//====================
// 変数
//====================
private:
	Player* player_;	//!< プレイヤー
	BulletPhysicsObject* bullet_object_;	//!< バレットオブジェクト

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

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief 平行移動入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief カメラ無し平行移動入力関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InputTranslationNotCamera();
};



#endif