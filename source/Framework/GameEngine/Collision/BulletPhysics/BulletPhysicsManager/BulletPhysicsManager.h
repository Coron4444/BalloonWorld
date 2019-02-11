//================================================================================
//!	@file	 BulletPhysicsManager.h
//!	@brief	 バレットフィジックスマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================
#ifndef	_BULLET_PHYSICS_MANAGER_H_
#define _BULLET_PHYSICS_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)
#include <vector>
#include <list>

#include "../BulletPhysicsObject.h"
#include "../BulletPhysicsConstraint.h"

#include <Tool/Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class BulletPhysicsDebug;
class Camera;



//************************************************************														   
//! @brief   バレットフィジックスマネージャClass(Singleton)
//!
//! @details バレットフィジックスのマネージャClass(Singleton)
//************************************************************
class BulletPhysicsManager
{
//====================
// 定数
//====================
private:
	static const btVector3 DEFULT_GRAVITY;	//!< デフォルトの重力値
	static const btScalar TIME_STEP;		//!< 更新すると進む秒数
	static const int MAX_SUB_STEP;			//!< 更新の細かさ


//====================
// static変数
//====================
private:
	static BulletPhysicsManager* instance_;		//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval BulletPhysicsManager* インスタンス
	//----------------------------------------
	static BulletPhysicsManager* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();


//====================
// 変数
//====================
private:
	btDefaultCollisionConfiguration* configuration_ = nullptr;	//!< 衝突計算の設定
	btCollisionDispatcher* dispatcher_ = nullptr;				//!< 衝突計算の設定
	btDbvtBroadphase* broadphase_ = nullptr;					//!< ブロードフェーズ法(衝突する可能性のあるオブジェクトの検出)
	btSequentialImpulseConstraintSolver* solver_ = nullptr;		//!< 拘束ソルバ(オブジェクトの重なり解消などの設定)
	btDynamicsWorld* dynamics_world_ = nullptr;					//!< Bulletワールド
	BulletPhysicsDebug* debug_ = nullptr;						//!< デバッグ表示
	std::list<BulletPhysicsObject*> object_;					//!< オブジェクトリスト
	std::list<BulletPhysicsConstraint*> constraint_;			//!< 拘束


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief デバッグ設定関数
	//! @details
	//! @param value デバッグフラグ
	//! @retval void なし
	//----------------------------------------
	void setDebug(bool value);

	//----------------------------------------
	//! @brief 球オブジェクト取得関数
	//! @details
	//! @param mass       質量
	//! @param inertia    慣性モーメント
	//! @param position   座標
	//! @param quaternion クォータニオン
	//! @param radius     半径
	//! @retval BulletPhysicsObject* 球オブジェクト
	//----------------------------------------
	BulletPhysicsObject* getpObjectSphere(float mass, Vec3 inertia, Vec3 position,
										  Quaternion quaternion, float radius);

	//----------------------------------------
	//! @brief OBBオブジェクト取得関数
	//! @details
	//! @param mass             質量
	//! @param inertia          慣性モーメント
	//! @param position         座標
	//! @param quaternion       クォータニオン
	//! @param edge_half_length 辺の半分の長さ
	//! @retval BulletPhysicsObject* OBBオブジェクト
	//----------------------------------------
	BulletPhysicsObject* getpObjectOBB(float mass, Vec3 inertia, Vec3 position,
									   Quaternion quaternion, Vec3 edge_half_length);

	//----------------------------------------
	//! @brief カプセルオブジェクト取得関数
	//! @details
	//! @param mass       質量
	//! @param inertia    慣性モーメント
	//! @param position   座標
	//! @param quaternion クォータニオン
	//! @param radius     半径
	//! @param height     高さ
	//! @retval BulletPhysicsObject* 球オブジェクト
	//----------------------------------------
	BulletPhysicsObject* getpObjectCapsule(float mass, Vec3 inertia, Vec3 position,
										   Quaternion quaternion, float radius, float height);

	//----------------------------------------
	//! @brief ポイントとポイントの拘束設定関数
	//! @details
	//! @param bullet_object0 オブジェクト0
	//! @param bullet_object1 オブジェクト1
	//! @param point0         ポイント0
	//! @param point1         ポイント1
	//! @retval BulletPhysicsConstraint* 拘束
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintPointToPoint(BulletPhysicsObject* bullet_object0,
													   BulletPhysicsObject* bullet_object1,
													   Vec3 point0, Vec3 point1);

	//----------------------------------------
	//! @brief 1つの軸を回転する拘束初期化関数
	//! @details
	//! @param bullet_object0 オブジェクト0
	//! @param bullet_object1 オブジェクト1
	//! @param point0      ポイント0(ローカル座標)
	//! @param point1      ポイント1(ローカル座標)
	//! @param angle_min    最小角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max    最大角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param axis        回転軸
	//! @retval void なし
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintHinge(BulletPhysicsObject* bullet_object0,
												BulletPhysicsObject* bullet_object1,
												Vec3 point0, Vec3 point1,
												float angle_min, float angle_max,
												Vec3 axis = {0.0f, 1.0f, 0.0f});

	//----------------------------------------
	//! @brief 接続点とそれを中心とした2軸の拘束設定関数
	//! @details
	//! @param *bullet_object0 オブジェクト0
	//! @param *bullet_object1 オブジェクト1
	//! @param anchor          接続点(ワールド座標)
	//! @param angle_min0      最小角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_min1      最小角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max0      最大角度0(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param angle_max1      最大角度1(1.0f~0.0fで1.0fに近いほど自由が利く)
	//! @param axis0           回転軸0
	//! @param axis1           回転軸1
	//! @retval BulletPhysicsConstraint* 拘束
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintUniversal(BulletPhysicsObject* bullet_object0,
													BulletPhysicsObject* bullet_object1,
													Vec3 anchor,
													float angle_min0, float angle_min1,
													float angle_max0, float angle_max1,
													Vec3 axis0 = {1.0f, 0.0f, 0.0f},
													Vec3 axis1 = {0.0f, 0.0f, 1.0f});


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	BulletPhysicsManager();

public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details
	//! @param camera カメラ
	//! @retval void なし
	//----------------------------------------
	void DrawDebug(Camera* camera);

	//----------------------------------------
	//! @brief オブジェクトリストから解放関数
	//! @details
	//! @param *object オブジェクト自身のポインタ
	//! @retval void なし
	//----------------------------------------
	void ReleaseFromTheObjectList(BulletPhysicsObject* object);

	//----------------------------------------
	//! @brief 拘束リストから解放関数
	//! @details
	//! @param *constraint 拘束自身のポインタ
	//! @retval void なし
	//----------------------------------------
	void ReleaseFromTheConstraintList(BulletPhysicsConstraint* constraint);


//====================
// 消去済み関数
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif