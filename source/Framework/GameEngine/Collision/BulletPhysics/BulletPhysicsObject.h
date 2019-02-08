//================================================================================
//!	@file	 BulletPhysicsObject.h
//!	@brief	 バレットフィジックスオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/08
//================================================================================
#ifndef	_BULLET_PHYSICS_OBJECT_H_
#define _BULLET_PHYSICS_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)



//************************************************************														   
//! @brief   バレットフィジックスオブジェクトClass
//!
//! @details バレットフィジックスのオブジェクトClass
//************************************************************
class BulletPhysicsObject
{
//====================
// 変数
//====================
private:
	btCollisionShape* collision_shape_ = nullptr;	//!< 衝突形状
	btDefaultMotionState* motion_state_ = nullptr;	//!< 外部から剛体を操作するハンドル
	btRigidBody* rigid_body_ = nullptr;				//!< 剛体
	int reference_counter_ = 0;						//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 衝突形状取得関数
	//! @details
	//! @param void なし
	//! @retval btCollisionShape* 衝突形状
	//----------------------------------------
	btCollisionShape* getpCollisionShape();

	//----------------------------------------
	//! @brief 外部から剛体を操作するハンドル得関数
	//! @details
	//! @param void なし
	//! @retval btDefaultMotionState* 外部から剛体を操作するハンドル
	//----------------------------------------
	btDefaultMotionState* getpMotionState();

	//----------------------------------------
	//! @brief 剛体取得関数
	//! @details
	//! @param void なし
	//! @retval btRigidBody* 剛体
	//----------------------------------------
	btRigidBody* getpRigidBody();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 球初期化関数
	//! @details
	//! @param mass       質量
	//! @param inertia    慣性モーメント
	//! @param position   座標
	//! @param quaternion クォータニオン
	//! @param radius     半径
	//! @retval void なし
	//----------------------------------------
	void InitSphere(float mass, btVector3 inertia,
					btVector3 position, btQuaternion quaternion,
					float radius);

	//----------------------------------------
	//! @brief OBB初期化関数
	//! @details
	//! @param mass             質量
	//! @param inertia          慣性モーメント
	//! @param position         座標
	//! @param quaternion       クォータニオン
	//! @param edge_half_length 辺の半分の長さ
	//! @retval void なし
	//----------------------------------------
	void InitOBB(float mass, btVector3 inertia,
				 btVector3 position, btQuaternion quaternion,
				 btVector3 edge_half_length);


	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief 強制解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

private:
	//----------------------------------------
	//! @brief 共通初期化関数
	//! @details
	//! @param mass       質量
	//! @param inertia    慣性モーメント
	//! @param position   座標
	//! @param quaternion クォータニオン
	//! @retval void なし
	//----------------------------------------
	void InitCommon(float mass, btVector3 inertia,
					btVector3 position, btQuaternion quaternion);
};



#endif