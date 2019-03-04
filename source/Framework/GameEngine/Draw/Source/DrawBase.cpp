//================================================================================
//!	@file	 DrawBase.cpp
//!	@brief	 描画BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../DrawBase.h"



//****************************************
// プロパティ定義
//****************************************
DrawOrderList* DrawBase::getpDrawOrderList() 
{
	return &order_list_; 
}



DrawCommonData* DrawBase::getpDrawCommonData()
{
	return common_data_;
}


void DrawBase::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



//****************************************
// 関数定義
//****************************************
DrawBase::~DrawBase()
{
}