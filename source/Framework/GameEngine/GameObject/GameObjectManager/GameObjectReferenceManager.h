//================================================================================
//!	@file	 GameObjectReferenceManager.h
//!	@brief	 ゲームオブジェクト参照マネージャClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/15
//================================================================================
#ifndef	_GAME_OBJECT_REFERENCE_MANAGER_H_
#define _GAME_OBJECT_REFERENCE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <unordered_map>

#include <Tool/LimitedPointerArray.h>



//****************************************
// クラス宣言
//****************************************
class GameObjectBase;


//************************************************************														   
//! @brief   ゲームオブジェクト参照マネージャClass
//!
//! @details ゲームオブジェクトの参照マネージャClass
//************************************************************
class GameObjectReferenceManager
{
//====================
// 構造体定義
//====================
public:
	//****************************************											   
	//! @brief   参照データClass
	//!
	//! @details 参照のデータClass
	//****************************************
	struct ReferenceData
	{
	//====================
	// 変数
	//====================
	public:
		GameObjectBase* reference_source_;			//!< 参照元オブジェクト
		GameObjectBase* reference_destination_;		//!< 参照先オブジェクト
		void* reference_pointer_;					//!< 参照ポインタ
		int	registration_index_;					//!< 登録インデックス

	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief コンストラクタ
		//! @details
		//! @param source      参照元オブジェクト
		//! @param pointer     参照ポインタ
		//! @param destination 参照先オブジェクト
		//----------------------------------------
		ReferenceData(GameObjectBase* source, void* pointer,
					  GameObjectBase* destination);
	};


//====================
// 定数
//====================
private:
	static const unsigned ARRAY_NUM = 1000;		//!< 配列数


//====================
// 変数
//====================
private:
	std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> source_map_;		//!< キーのオブジェクトが参照元のマップ
	std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> destination_map_;	//!< // キーのオブジェクトが参照先のマップ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デストラクタ
	//! @param void なし
	//----------------------------------------
	~GameObjectReferenceManager();

	//----------------------------------------
	//! @brief 参照データ追加関数
	//! @details
	//! @param source      参照元オブジェクト
	//! @param pointer     参照ポインタ
	//! @param destination 参照先オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddReference(GameObjectBase* source, void* pointer,
					  GameObjectBase* destination);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void Release(GameObjectBase* object);

	//----------------------------------------
	//! @brief 全開放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AllRelease();

private:
	//----------------------------------------
	//! @brief 参照元追加関数
	//! @details
	//! @param source      参照元オブジェクト
	//! @param pointer     参照ポインタ
	//! @param destination 参照先オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddSource(GameObjectBase* source, void* pointer,
				   GameObjectBase* destination);

	//----------------------------------------
	//! @brief 参照先追加関数
	//! @details
	//! @param source      参照元オブジェクト
	//! @param pointer     参照ポインタ
	//! @param destination 参照先オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddDestination(GameObjectBase* source, void* pointer,
						GameObjectBase* destination);

	//----------------------------------------
	//! @brief 参照元解放関数
	//! @details
	//! @param object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseSource(GameObjectBase* object);

	//----------------------------------------
	//! @brief 参照先解放関数
	//! @details
	//! @param object ゲームオブジェクト基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseDestination(GameObjectBase* object);
};



#endif
