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



//****************************************
// クラス宣言
//****************************************
class BulletPhysicsDebug;
class BulletPhysicsObject;
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

	// 組み合わせ
	btCollisionShape* comp_shape_[2];
	btRigidBody* comp_rigid_body_;
	btDefaultMotionState* comp_motion_state_;
	btCompoundShape* comp_;

	// 拘束
	std::vector<btCollisionShape*> constraint_shape_;
	std::vector<btRigidBody*> constraint_rigid_body_;
	std::vector<btDefaultMotionState*> constraint_motion_state_;
	std::vector<btTypedConstraint*> constraint_;


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
	//! @brief モーションステート取得関数
	//! @details
	//! @param void なし
	//! @retval btDefaultMotionState* モーションステート取得
	//----------------------------------------
	btDefaultMotionState* getpMotionState();

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
	//! @brief リストから解放関数
	//! @details
	//! @param *object オブジェクト自身のポインタ
	//! @retval void なし
	//----------------------------------------
	void ReleaseFromTheList(BulletPhysicsObject* object);


//====================
// 消去済み関数
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif