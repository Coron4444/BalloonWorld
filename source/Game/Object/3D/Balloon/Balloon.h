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
#include <vector>

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
	static const Vec3 OBB_EDGE_LENGTH_HALF;
	static const float SPHERE_RADIUS;


//====================
// 変数
//====================
private:
	std::vector<BulletPhysicsObject*> all_object_;				//!< 総オブジェクト
	std::vector<BulletPhysicsConstraint*> object_constraint_;	//!< オブジェクトの拘束
	std::vector<Transform> object_transform_;					//!< オブジェクト変形
	

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 総オブジェクト数取得関数
	//! @details
	//! @param void なし
	//! @retval int 総オブジェクト数
	//----------------------------------------
	int getAllObjectNum();

	//----------------------------------------
	//! @brief オブジェクトの拘束数取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned 総オブジェクト数
	//----------------------------------------
	int getObjectConstraintNum();

	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param index インデックス
	//! @retval BulletPhysicsObject* オブジェクト
	//----------------------------------------
	BulletPhysicsObject* getpObject(unsigned index);

	//----------------------------------------
	//! @brief オブジェクトの拘束取得関数
	//! @details
	//! @param index インデックス
	//! @retval BulletPhysicsConstraint* オブジェクトの拘束
	//----------------------------------------
	BulletPhysicsConstraint* getpObjectConstraint(unsigned index);

	//----------------------------------------
	//! @brief オブジェクトの変形取得関数
	//! @details
	//! @param index インデックス
	//! @retval Transform* オブジェクトの変形
	//----------------------------------------
	Transform* getpObjectTransform(unsigned index);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *update           更新基底クラス
	//! @param *draw             描画基底クラス
	//! @param balloon_line_num  風船の線の数
	//! @retval void なし
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, unsigned balloon_line_num);

	//----------------------------------------
	//! @brief 拘束解放関数
	//! @details
	//! @param index インデックス
	//! @retval void なし
	//----------------------------------------
	void ReleaseConstraint(unsigned index);


private:
	//----------------------------------------
	//! @brief バレットオブジェクト初期化関数
	//! @details
	//! @param balloon_line_num 風船の線の数
	//! @retval void なし
	//----------------------------------------
	void InitBulletPhysicsObject(unsigned balloon_line_num);
};



#endif