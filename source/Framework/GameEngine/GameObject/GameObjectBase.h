//================================================================================
//!	@file	 GameObjectBase.h
//!	@brief	 ゲームオブジェクトBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/03/22
//================================================================================
#ifndef	_GAME_OBJECT_BASE_H_
#define _GAME_OBJECT_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../Update/UpdateBase.h"
#include "../Draw/DrawBase.h"
#include "../Collision/CollisionBase.h"

#include <Tool/Transform.h>
#include <Tool/Physics.h>



//************************************************************														   
//! @brief   ゲームオブジェクトBaseClass
//!
//! @details ゲームオブジェクトのBaseClass
//************************************************************
class GameObjectBase
{
//====================
// 変数
//====================
private:
	Transform transform_;		//!< 変形
	Physics*  physics_;			//!< 物理

	bool is_registration_;		//!< 登録フラグ

	UpdateBase*    update_;		//!< 更新基底クラス
	DrawBase*      draw_;		//!< 描画基底クラス
	CollisionBase* collision_;	//!< 衝突基底クラス


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 変形取得関数
	//! @details
	//! @param void なし
	//! @retval Transform* 変形
	//----------------------------------------
	Transform* getpTransform();

	//----------------------------------------
	//! @brief 物理取得関数
	//! @details
	//! @param void なし
	//! @retval Transform* 変形
	//----------------------------------------
	Physics* getpPhysics();

	//----------------------------------------
	//! @brief 全基底クラス設定関数
	//! @details
	//! @param update    更新基底クラス
	//! @param draw      描画基底クラス
	//! @param collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setAllComponent(UpdateBase* update, DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 更新基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval UpdateBase* 更新基底クラス
	//----------------------------------------
	UpdateBase* getpUpdate();

	//----------------------------------------
	//! @brief 更新基底クラス設定関数
	//! @details
	//! @param value 更新基底クラス
	//! @retval void なし
	//----------------------------------------
	void setUpdate(UpdateBase* value);

	//----------------------------------------
	//! @brief 描画基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval DrawBase* 描画基底クラス
	//----------------------------------------
	DrawBase* getpDraw();

	//----------------------------------------
	//! @brief 描画基底クラス設定関数
	//! @details
	//! @param value 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void setDraw(DrawBase* value);

	//----------------------------------------
	//! @brief 衝突基底クラス取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionBase* 衝突基底クラス
	//----------------------------------------
	CollisionBase* getpCollision();

	//----------------------------------------
	//! @brief 衝突基底クラス設定関数
	//! @details
	//! @param value 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setCollision(CollisionBase* value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param is_registration 登録フラグ
	//----------------------------------------
	GameObjectBase(bool is_registration = true);

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~GameObjectBase();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param update    更新基底クラス
	//! @param draw      描画基底クラス
	//! @param collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit();

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset();

	//----------------------------------------
	//! @brief 物理生成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreatePhysics();
:

private:
	//----------------------------------------
	//! @brief コンポーネント初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitComponent();

	//----------------------------------------
	//! @brief コンポーネント終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitComponent();

	//----------------------------------------
	//! @brief コンポーネントリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetComponent();

	//----------------------------------------
	//! @brief 描画共通データ追加関数
	//! @details
	//! @param draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddDrawCommonData(DrawBase* draw);
};



#endif
