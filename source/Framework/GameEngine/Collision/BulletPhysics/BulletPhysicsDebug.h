//================================================================================
//!	@file	 BulletPhysicsDebug.h
//!	@brief	 バレットフィジックスデバッグClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/07
//================================================================================
#ifndef	_BULLET_PHYSICS_DEBUG_H_
#define _BULLET_PHYSICS_DEBUG_H_



//****************************************
// インクルード文
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#pragma warning(pop)



//****************************************
// クラス宣言
//****************************************
class Camera;
class Transform;



//************************************************************														   
//! @brief   バレットフィジックスデバッグClass
//!
//! @details バレットフィジックスのデバッグClass
//************************************************************
class BulletPhysicsDebug : public btIDebugDraw
{
//====================
// 変数
//====================
private:
	int debug_mode_ = 0;					//!< デバッグモード
	RendererDirectX9::VERTEX_3D vertex_[2];	//!< 頂点
	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< デバイス
	Transform transform_;		//!< 変形


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief デバッグモード取得関数
	//! @details
	//! @param void なし
	//! @retval int デバッグモード
	//----------------------------------------
	int getDebugMode() const override;

	//----------------------------------------
	//! @brief デバッグモード設定関数
	//! @details
	//! @param value デバッグモード
	//! @retval void なし
	//----------------------------------------
	void setDebugMode(int value) override;


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
	void Init();

	//----------------------------------------
	//! @brief 線の描画関数
	//! @details
	//! @param from  開始点
	//! @param to    終端点
	//! @param color 色
	//! @retval void なし
	//----------------------------------------
	virtual void drawLine(const btVector3& from, const btVector3& to,
						  const btVector3& color) override;

	//----------------------------------------
	//! @brief 描画前設定関数
	//! @details
	//! @param camera カメラ
	//! @retval void なし
	//----------------------------------------
	void DrawSettingBefore(Camera* camera);

	//----------------------------------------
	//! @brief 描画後設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DrawSettingAfter();

	// 未対応
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
						  btScalar distance, int lifeTime, const btVector3& color) override;
	void reportErrorWarning(const char* warningString) override;
	void draw3dText(const btVector3& location, const char* textString) override;
};



#endif