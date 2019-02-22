//================================================================================
//!	@file	 ClearLogo.h
//!	@brief	 �N���A���SClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_CLEAR_LOGO_H_
#define _CLEAR_LOGO_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �N���A���SClass
//!
//! @details �N���A���S��Class
//************************************************************
class ClearLogo : public GameObjectNull
{
private:
	int score_ = 0;

public:
	int getScore();
	void setScore(int value);

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw);
};



#endif