//================================================================================
//!	@file	 GameObjectManager.h
//!	@brief	 ゲームオブジェクトマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2018/07/13
//================================================================================
#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include "UpdateManager.h"
#include "../../Draw/DrawManager/DrawManager.h"
#include "../../Collision/CollisionManager/CollisionManager.h"

#include <Tool/LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   ゲームオブジェクトマネージャClass(Singleton)
//!
//! @details ゲームオブジェクトのマネージャClass(Singleton)
//************************************************************
class GameObjectManager
{
//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 1000;		//!< 配列数


//====================
// static変数
//====================
private:
	static GameObjectManager* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval GameObjectManager* インスタンス
	//----------------------------------------
	static GameObjectManager* getpInstance();


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
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> all_game_object_;	//!< 全ゲームオブジェクト配列
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_add_;			//!< 追加待ち配列
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_release_;		//!< 解放待ち配列

	UpdateManager update_manager_;					//!< 更新マネージャ
	DrawManager draw_manager_;						//!< 描画マネージャ
	CollisionManager collision_manager_;			//!< 衝突マネージャ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 更新マネージャ取得関数
	//! @details
	//! @param void なし
	//! @retval UpdateManager* 更新マネージャ
	//----------------------------------------
	UpdateManager* getpUpdateManager();

	//----------------------------------------
	//! @brief 描画マネージャ取得関数
	//! @details
	//! @param void なし
	//! @retval DrawManager* 描画マネージャ
	//----------------------------------------
	DrawManager* getpDrawManager();

	//----------------------------------------
	//! @brief 衝突マネージャ取得関数
	//! @details
	//! @param void なし
	//! @retval CollisionManager* 衝突マネージャ
	//----------------------------------------
	CollisionManager* getpCollisionManager();


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	GameObjectManager();

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
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief ゲームオブジェクト基底クラス追加関数
	//! @details
	//! @param *game_object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddGameObjectBase(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief ゲームオブジェクト基底クラス解放関数
	//! @details
	//! @param *game_object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseGameObjectBase(GameObjectBase* game_object);

private:
	//----------------------------------------
	//! @brief 追加待ちの追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief 解放待ちの解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief コンポーネントとゲームオブジェクト基底クラスをマネージャーへ追加関数
	//! @details
	//! @param *game_object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddComponentAndGameObjectBaseToManager(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief コンポーネントとゲームオブジェクト基底クラスをマネージャーから解放関数
	//! @details
	//! @param *game_object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseComponentAndGameObjectBaseFromManager(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();


//====================
// 消去済み関数
//====================
private:
	GameObjectManager(const GameObjectManager& class_name) = delete;
	GameObjectManager& operator = (const GameObjectManager& class_name) = delete;
};



#endif
