//================================================================================
//!	@file	 FieldFactory.cpp
//!	@brief	 地面生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/23
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../FieldFactory.h"
#include "../Field.h"
#include "../FieldDraw.h"



//****************************************
// 関数定義
//****************************************
Field* FieldFactory::Create()
{
	Field* temp = new Field();
	temp->Init(new FieldDraw());
	return temp;
}