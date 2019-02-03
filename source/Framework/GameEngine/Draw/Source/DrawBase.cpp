//================================================================================
//!	@file	 DrawBase.cpp
//!	@brief	 �`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../DrawBase.h"



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
DrawBase::~DrawBase()
{
}