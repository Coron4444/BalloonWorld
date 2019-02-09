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

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   バレットフィジックスオブジェクトClass
//!
//! @details バレットフィジックスのオブジェクトClass
//************************************************************
class BulletPhysicsObject
{
//====================
// 列挙型定義
//====================
private:
	enum class Type
	{
		NONE = -1,
		SPHERE,
		OBB,
		MAX
	};


//====================
// 変数
//====================
private:
	Type type_ = Type::NONE;						//!< タイプ
	btCollisionShape* collision_shape_ = nullptr;	//!< 衝突形状
	btDefaultMotionState* motion_state_ = nullptr;	//!< 外部から剛体を操作するハンドル
	btRigidBody* rigid_body_ = nullptr;				//!< 剛体
	int reference_counter_ = 0;						//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type タイプ
	//----------------------------------------
	Type getType();

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

	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vec3 座標
	//----------------------------------------
	Vec3 getPosition();

	//----------------------------------------
	//! @brief クォータニオン取得関数
	//! @details
	//! @param void なし
	//! @retval Quaternion クォータニオン
	//----------------------------------------
	Quaternion getQuaternion();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 球初期化関数
	//! @details
	//! @param mass        質量
	//! @param *inertia    慣性モーメント
	//! @param *position   座標
	//! @param *quaternion クォータニオン
	//! @param radius      半径
	//! @retval void なし
	//----------------------------------------
	void InitSphere(float mass, Vec3* inertia, Vec3* position,
					Quaternion* quaternion, float radius);

	//----------------------------------------
	//! @brief OBB初期化関数
	//! @details
	//! @param mass              質量
	//! @param *inertia          慣性モーメント
	//! @param *position         座標
	//! @param *quaternion       クォータニオン
	//! @param *edge_half_length 辺の半分の長さ
	//! @retval void なし
	//----------------------------------------
	void InitOBB(float mass, Vec3* inertia, Vec3* position, 
				 Quaternion* quaternion, Vec3* edge_half_length);

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

	//----------------------------------------
	//! @brief 初速度追加関数
	//! @details
	//! @param velocity    初速度
	//! @param power_point 力点
	//! @retval void なし
	//----------------------------------------
	void AddVelocity(Vec3 velocity, Vec3 power_point = {0.0f, 0.0f, 0.0f});

	//----------------------------------------
	//! @brief 加速度追加関数
	//! @details
	//! @param acceleration 加速度
	//! @param power_point  力点
	//! @retval void なし
	//----------------------------------------
	void AddAcceleration(Vec3 acceleration, Vec3 power_point = {0.0f, 0.0f, 0.0f});

private:
	//----------------------------------------
	//! @brief 共通初期化関数
	//! @details
	//! @param mass        質量
	//! @param *inertia    慣性モーメント
	//! @param *position   座標
	//! @param *quaternion クォータニオン
	//! @retval void なし
	//----------------------------------------
	void InitCommon(float mass, Vec3* inertia,
					Vec3* position, Quaternion* quaternion);
};



#endif