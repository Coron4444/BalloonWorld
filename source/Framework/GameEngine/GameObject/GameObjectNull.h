//================================================================================
//!	@file	 GameObjectNull.h
//!	@brief	 �Q�[���I�u�W�F�N�g��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/30
//================================================================================
#ifndef	_GAME_OBJECT_NULL_H_
#define _GAME_OBJECT_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "GameObjectBase.h"



//************************************************************														   
//! @brief   �Q�[���I�u�W�F�N�g��Class
//!
//! @details �Q�[���I�u�W�F�N�g�̋�Class
//************************************************************
class GameObjectNull : public GameObjectBase
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param is_registration �o�^�t���O
	//----------------------------------------
	GameObjectNull(bool is_registration = true);

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~GameObjectNull();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() override;
};



#endif
