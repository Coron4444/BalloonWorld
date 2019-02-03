//================================================================================
//!	@file	 LimitedPointerArray.h
//!	@brief	 有限ポインター配列Class
//! @details template
//!	@author  Kai Araki									@date 2018/04/18
//================================================================================
#ifndef	_LIMITED_POINTER_ARRAY_H_
#define _LIMITED_POINTER_ARRAY_H_



//****************************************
// インクルード文
//****************************************
#include <unordered_map>

#include "SafeRelease.h"



//************************************************************														   
//! @brief   有限ポインター配列Class(template)
//!
//! @details 有限数のポインターを確保した配列Class(template)
//************************************************************
template<class Type, unsigned ARRAY_NUM = 100000>
class LimitedPointerArray
{
//====================
// 変数
//====================
private:
	Type array_[ARRAY_NUM];									//!< 配列
	unsigned end_index_ = 0;								//!< 末尾インデックス
	std::unordered_map<Type, unsigned> registration_map_;	//!< 登録マップ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト取得関数
	//! @details
	//! @param index インデックス
	//! @retval void なし
	//----------------------------------------
	Type getObject(unsigned index)
	{
		return array_[index];
	}

	//----------------------------------------
	//! @brief 末尾インデックス取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	unsigned getEndIndex()
	{
		return end_index_;
	}

	//----------------------------------------
	//! @brief 配列数取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	unsigned getArrayNum()
	{
		return ARRAY_NUM;
	}

	//----------------------------------------
	//! @brief インデックス取得関数
	//! @details
	//! @param object オブジェクト
	//! @retval void なし
	//----------------------------------------
	unsigned getIndex(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);

		// インデックス番号を返す
		if (iterator != registration_map_.end())
		{
			return iterator->second;
		}
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	LimitedPointerArray()
	{
		// 配列の初期化
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			array_[i] = nullptr;
		}

		// マップの初期化
		registration_map_.clear();
	}

	//----------------------------------------
	//! @brief 配列に追加関数
	//! @details
	//! @param object 追加オブジェクト
	//! @retval void なし
	//----------------------------------------
	void AddToArray(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator != registration_map_.end()) return;

		// 追加
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			if (array_[i] != nullptr) continue;

			// 配列に追加
			array_[i] = object;

			// マップに登録
			registration_map_.insert(std::make_pair(object, i));

			// エンドポインタの更新
			if (end_index_ < (i + 1))
			{
				end_index_ = (i + 1);
			}
			return;
		}
	}

	//----------------------------------------
	//! @brief 配列の上書き関数
	//! @details
	//! @param old_object 古いオブジェクト
	//! @param new_object 新規オブジェクト
	//! @retval void なし
	//----------------------------------------
	void OverwriteArray(Type old_object, Type new_object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// 配列の上書き
			array_[iterator->second] = new_object;

			// 新規オブジェクトを登録及び古いオブジェクトの削除
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);
		}
		else
		{
			// 古いオブジェクトがないため新規扱い
			AddToArray(new_object);
		}
	}

	//----------------------------------------
	//! @brief 配列の上書きと解放関数
	//! @details
	//! @param old_object 古いオブジェクト
	//! @param new_object 新規オブジェクト
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayAndReleaseOldObject(Type old_object, Type new_object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// 配列の上書き
			array_[iterator->second] = new_object;

			// 新規オブジェクトを登録及び古いオブジェクトの削除
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);

			// 古いオブジェクトの解放
			SafeRelease::Normal(&old_object);
		}
		else
		{
			// 古いオブジェクトがないため新規扱い
			AddToArray(new_object);
		}
	}

	//----------------------------------------
	//! @brief リセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset()
	{
		// 配列からの削除
		for (unsigned i = 0; i < end_index_; i++)
		{
			array_[i] = nullptr;
		}

		// マップのリセット
		registration_map_.clear();

		// エンドポインタをリセット
		end_index_ = 0;
	}

	//----------------------------------------
	//! @brief 登録オブジェクトの解放と配列のリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseObjectAndReset()
	{
		// 登録先の解放と配列からの削除
		for (unsigned i = 0; i < end_index_; i++)
		{
			SafeRelease::Normal(&array_[i]);
			array_[i] = nullptr;
		}

		// マップのリセット
		registration_map_.clear();

		// エンドポインタをリセット
		end_index_ = 0;
	}

	//----------------------------------------
	//! @brief 配列から削除関数
	//! @details
	//! @param object 削除オブジェクト
	//! @retval void なし
	//----------------------------------------
	void DeleteFromArray(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// 配列から削除及び、登録の解除
		array_[iterator->second] = nullptr;
		registration_map_.erase(object);
	}

	//----------------------------------------
	//! @brief ソート関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Sort()
	{
		int temp_num = 0;

		for (unsigned i = 0; i < end_index_; i++)
		{
			if (array_[i] != nullptr) continue;

			temp_num++;

			for (unsigned k = (end_index_ - 1); k > i; k--)
			{
				if (array_[k] == nullptr) continue;

				// オブジェクトを入れ替える
				array_[i] = array_[k];
				array_[k] = nullptr;

				// マップの更新
				registration_map_.find(array_[i])->second = i;
				break;
			}
		}

		// エンドポインタの更新
		end_index_ -= temp_num;
	}

	//----------------------------------------
	//! @brief 配列からの削除とソート関数
	//! @details
	//! @param object 削除オブジェクト
	//! @retval void なし
	//----------------------------------------
	void DeleteFromArrayAndSort(Type object)
	{
		// 登録の確認
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// 削除先が配列の末端かどうか
		if (iterator->second == (end_index_ - 1))
		{
			// 配列から削除
			array_[iterator->second] = nullptr;
		}
		else
		{
			// ソート
			for (unsigned i = (end_index_ - 1); i > iterator->second; i--)
			{
				if (array_[i] == nullptr) continue;

				// オブジェクトを入れ替える
				array_[iterator->second] = array_[i];
				array_[i] = nullptr;

				// マップの更新
				registration_map_.find(array_[iterator->second])->second = iterator->second;

				break;
			}
		}

		// マップから削除
		registration_map_.erase(object);

		// エンドポインタの更新
		end_index_--;
	}

	//----------------------------------------
	//! @brief 配列の2つのオブジェクトを並び替え関数
	//! @details
	//! @param index0 インデックス0
	//! @param index0 インデックス1
	//! @retval void なし
	//----------------------------------------
	void SortTheTwoObject(unsigned index0, unsigned index1)
	{
		// マップの更新
		unsigned temp_index = registration_map_.find(array_[index0])->second;
		registration_map_.find(array_[index0])->second = registration_map_.find(array_[index1])->second;
		registration_map_.find(array_[index1])->second = temp_index;

		// 配列の並び替え
		Type temp = array_[index0];
		array_[index0] = array_[index1];
		array_[index1] = temp;
	}

	//----------------------------------------
	//! @brief 登録数が最大か判定関数
	//! @details
	//! @param void なし
	//! @retval bool 登録数が最大ならtrue
	//----------------------------------------
	bool IsMax()
	{
		return ARRAY_NUM == (end_index_ + 1);
	}
};



#endif
