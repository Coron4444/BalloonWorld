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
#ifdef _DEBUG
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
#endif

#include <Tool/Transform.h>
#include <Tool/Physics.h>



//****************************************
// クラス宣言
//****************************************
class UpdateBase;
class DrawBase;
class CollisionBase;



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
	bool is_input_ = true;		//!< 入力フラグ
	bool is_update_ = true;		//!< 更新フラグ

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
	//! @brief 入力フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 入力フラグ
	//----------------------------------------
	bool getIsInput();

	//----------------------------------------
	//! @brief 入力フラグ取得関数
	//! @details
	//! @param value 入力フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsInput(bool value);

	//----------------------------------------
	//! @brief 更新フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 更新フラグ
	//----------------------------------------
	bool getIsUpdate();

	//----------------------------------------
	//! @brief 更新フラグ取得関数
	//! @details
	//! @param value 更新フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsUpdate(bool value);

	//----------------------------------------
	//! @brief 全基底クラス設定関数
	//! @details
	//! @param draw      描画基底クラス
	//! @param collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void setAllComponent(DrawBase* draw, CollisionBase* collision);

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
	//! @param draw      描画基底クラス
	//! @param collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief 後更新関数
	//! @details 
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void LateUpdate() = 0;

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Reset() = 0;

	//----------------------------------------
	//! @brief デバッグ表示関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void DebugDisplay() = 0;

	//----------------------------------------
	//! @brief 物理生成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreatePhysics();

	
protected:
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

private:
	//----------------------------------------
	//! @brief コンポーネント初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitComponent();

	//----------------------------------------
	//! @brief 描画共通データ追加関数
	//! @details
	//! @param draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddDrawCommonData(DrawBase* draw);
};



#endif
