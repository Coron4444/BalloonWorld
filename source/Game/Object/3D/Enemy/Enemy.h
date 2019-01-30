//================================================================================
//!	@file	 Enemy.h
//!	@brief	 �GClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_ENEMY_H_
#define _ENEMY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �GClass
//!
//! @details �G��Class
//************************************************************
class Enemy : public GameObjectNull
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *update    �X�V���N���X
	//! @param *draw      �`����N���X
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);
};



#endif