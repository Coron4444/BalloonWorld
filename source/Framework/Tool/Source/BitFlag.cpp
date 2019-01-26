//================================================================================
//!	@file	 BitFlag.cpp
//!	@brief	 ビットフラグClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <limits.h>

#include "../BitFlag.h"



//****************************************
// プロパティ定義
//****************************************
unsigned BitFlag::getFlag()
{
	return flag_;
}



void BitFlag::setFlag(unsigned value)
{
	flag_ |= value;
}



//****************************************
// 関数定義
//****************************************
void BitFlag::Reset()
{
	flag_ = 0;
}



void BitFlag::Release(unsigned flag)
{
	flag_ &= ~flag;
}



bool BitFlag::CheckAny(unsigned flag)
{
	return (flag_ & flag) != 0;
}



bool BitFlag::CheckAll(unsigned flag)
{
	// チェックフラグを反転しORをとる
	flag = flag_ | ~flag;

	// 全てFlagが立っているかどうか
	return flag == UINT_MAX;
}