//================================================================================
//!	@file	 ClearLogo.cpp
//!	@brief	 �N���A���SClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ClearLogo.h"

int ClearLogo::getScore()
{
	return score_;
}

void ClearLogo::setScore(int value)
{
	score_ = value;
}

//****************************************
// �֐���`
//****************************************
void ClearLogo::Init(DrawBase* draw)
{
	// ���N���X�̏�����
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}