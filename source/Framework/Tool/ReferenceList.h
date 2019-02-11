//================================================================================
//!	@file	 ReferenceList.h
//!	@brief	 参照リストClass
//! @details template
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_REFERENCE_LIST_H_
#define _REFERENCE_LIST_H_



//****************************************
// インクルード文
//****************************************
#include <list>



//************************************************************														   
//! @brief   参照リストClass(template)
//!
//! @details 参照相手のリストClass(template)
//************************************************************
template<class Type>
class ReferenceList
{
//====================
// 変数
//====================
private:
	Type* object_ = nullptr;					//!< 自分のオブジェクト
	std::list<Type**> reference_opponent_;		//!< 参照相手ポインタリスト


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param value オブジェクト
	//! @retval void なし
	//----------------------------------------
	void setObject(Type* value)
	{
		object_ = value;
	}

	//----------------------------------------
	//! @brief 自分のオブジェクトポインタ取得関数
	//! @details
	//! @param **value 参照相手
	//! @retval Type* 自分のオブジェクトポインタ
	//----------------------------------------
	void getpMyPointer(Type** value)
	{
		*value = object_;
		for (auto contents : reference_opponent_)
		{
			if (value == contents) return;
		}
		reference_opponent_.push_back(value);
	}


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit()
	{
		// 参照先にnullptrを設定
		for (auto contents : reference_opponent_)
		{
			*contents = nullptr;
		}
	}

	//----------------------------------------
	//! @brief 参照解放関数
	//! @details
	//! @param **reference_opponent 参照相手
	//! @retval void なし
	//----------------------------------------
	void ReleaseReference(Type** reference_opponent)
	{
		for (auto iterator = reference_opponent_.begin(); iterator != reference_opponent_.end(); iterator++)
		{
			if (*iterator == reference_opponent)
			{
				reference_opponent_.erase(iterator);
				break;
			}
		}
	}
};



#endif
