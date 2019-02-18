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
// �萔
//====================
private:
	static const float SPEED;		//!< ���x


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw      �`����N���X
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;
};



#endif