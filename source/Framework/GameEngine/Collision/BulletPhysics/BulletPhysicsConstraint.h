//================================================================================
//!	@file	 BulletPhysicsConstraint.h
//!	@brief	 バレットフィジックス拘束Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/09
//================================================================================
#ifndef	_BULLET_PHYSICS_CONSTRAINT_H_
#define _BULLET_PHYSICS_CONSTRAINT_H_



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
//! @brief   バレットフィジックス拘束Class
//!
//! @details バレットフィジックスの拘束Class
//************************************************************
class BulletPhysicsConstraint
{
//====================
// 列挙型定義
//====================
private:
	enum class Type
	{
		NONE = -1,
		POINT_TO_POINT,
		MAX
	};


//====================
// 変数
//====================
private:
	btTypedConstraint* constraint_ = nullptr;		//!< 拘束
	Type type_ = Type::NONE;						//!< タイプ
	int reference_counter_ = 0;						//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 拘束取得関数
	//! @details
	//! @param void なし
	//! @retval btTypedConstraint* 拘束
	//----------------------------------------
	btTypedConstraint* getpConstraint();

	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type タイプ
	//----------------------------------------
	Type getType();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief ポイントとポイント拘束初期化関数
	//! @details
	//! @param *rigid_body0 剛体0
	//! @param *rigid_body1 剛体1
	//! @param *point0      ポイント0(ローカル座標)
	//! @param *point1      ポイント1(ローカル座標)
	//! @retval void なし
	//----------------------------------------
	void InitPointToPoint(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
						  Vector3D* point0, Vector3D* point1);

	//----------------------------------------
	//! @brief 1つの軸を回転する拘束初期化関数
	//! @details
	//! @param *rigid_body0 剛体0
	//! @param *rigid_body1 剛体1
	//! @param *point0      ポイント0(ローカル座標)
	//! @param *point1      ポイント1(ローカル座標)
	//! @param angle_min    最小角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max    最大角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param *axis        回転軸
	//! @retval void なし
	//----------------------------------------
	void InitHinge(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
				   Vector3D* point0, Vector3D* point1, 
				   float angle_min, float angle_max, Vector3D* axis);

	//----------------------------------------
	//! @brief 接続点とそれを中心とした2軸の拘束初期化関数
	//! @details
	//! @param *rigid_body0 剛体0
	//! @param *rigid_body1 剛体1
	//! @param *anchor      接続点(ワールド座標)
	//! @param angle_min0   最小角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_min1   最小角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max0   最大角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max1   最大角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param *axis0       回転軸0
	//! @param *axis1       回転軸1
	//! @retval void なし
	//----------------------------------------
	void InitUniversal(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
					   Vector3D* anchor, float angle_min0, float angle_min1,
					   float angle_max0, float angle_max1,
					   Vector3D* axis0, Vector3D* axis1);

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
};



#endif