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
	btDiscreteDynamicsWorld* dynamics_world_ = nullptr;			//!< Bulletワールド


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param void なし
	//! @retval TextureObject* オブジェクト
	//----------------------------------------


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



//====================
// 消去済み関数
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif