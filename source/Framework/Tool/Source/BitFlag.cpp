//================================================================================
//!	@file	 BitFlag.cpp
//!	@brief	 �r�b�g�t���OClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <limits.h>

#include "../BitFlag.h"



//****************************************
// �v���p�e�B��`
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
// �֐���`
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
	// �`�F�b�N�t���O�𔽓]��OR���Ƃ�
	flag = flag_ | ~flag;

	// �S��Flag�������Ă��邩�ǂ���
	return flag == UINT_MAX;
}