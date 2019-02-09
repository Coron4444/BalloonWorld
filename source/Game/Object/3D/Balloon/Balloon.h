//================================================================================
//!	@file	 Balloon.h
//!	@brief	 風船Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================
#ifndef	_BALLOON_H_
#define _BALLOON_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// クラス定義
//****************************************
class BulletPhysicsObject;
class BulletPhysicsConstraint;



//************************************************************														   
//! @brief   風船Class
//!
//! @details 風船のClass
//************************************************************
class Balloon : public GameObjectNull
{
//====================
// 定数
//====================
public:
	static const unsigned MAX_BULLET_OBJECT = 25;
	static const unsigned MAX_BULLET_CONSTRAINT = MAX_BULLET_OBJECT - 1;
	static const Vec3 OBB_EDGE_LENGTH_HALF;
	static const float SPHERE_RADIUS;


//====================
// 変数
//====================
public:
	BulletPhysicsObject* bullet_object_[MAX_BULLET_OBJECT];				//!< バレットオブジェクト
	BulletPhysicsConstraint* bullet_constraint_[MAX_BULLET_CONSTRAINT];	//!< バレット拘束
	Transform bullet_transform_[MAX_BULLET_OBJECT];
	

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *update 更新基底クラス
	//! @param *draw   描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw);

private:
	//----------------------------------------
	//! @brief バレットオブジェクト初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitBulletPhysicsObject();
};



#endif