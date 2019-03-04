//================================================================================
//!	@file	 BalloonNum.cpp
//!	@brief	 ���D��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonNum.h"



//****************************************
// �v���p�e�B��`
//****************************************
int BalloonNum::getBalloonNum()
{
	return balloon_num_;
}



void BalloonNum::setBalloonNum(int value)
{
	balloon_num_ = value;
}



//****************************************
// �֐���`
//****************************************
void BalloonNum::Init(DrawBase* draw)
{
	balloon_num_ = 0;

	// ���N���X�̏�����
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}