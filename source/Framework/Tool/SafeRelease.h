//================================================================================
//!	@file	 SafeRelease.h
//!	@brief	 セーフリリースClass
//! @details static
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_SAFE_RELEASE_H_
#define _SAFE_RELEASE_H_



//************************************************************														   
//! @brief   セーフリリース変換Class(static)
//!
//! @details 動的オブジェクトの安全な解放を担う関数群Class(static)
//************************************************************
class SafeRelease
{
//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param pointer 解放対象のポインタ
	//! @retval void なし
	//----------------------------------------
	template <class Type>
	static void Normal(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			delete *pointer;
			*pointer = nullptr;
		}
	}

	//----------------------------------------
	//! @brief Uninit付き解放関数
	//! @details
	//! @param pointer 解放対象のポインタ
	//! @retval void なし
	//----------------------------------------
	template <class Type>
	static void PlusUninit(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Uninit();
			delete *pointer;
			*pointer = nullptr;
		}
	}

	//----------------------------------------
	//! @brief Release付き解放関数
	//! @details
	//! @param pointer 解放対象のポインタ
	//! @retval void なし
	//----------------------------------------
	template <class Type>
	static void PlusRelease(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Release();
			*pointer = nullptr;
		}
	}
};



#endif