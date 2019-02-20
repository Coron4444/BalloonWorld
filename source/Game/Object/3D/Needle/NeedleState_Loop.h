//================================================================================
//!	@file	 NeedleState_Loop.h
//!	@brief	 ���X�e�[�g���[�vClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_NEEDLE_STATE_LOOP_H_
#define _NEEDLE_STATE_LOOP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Needle.h"



//************************************************************														   
//! @brief   ���X�e�[�g���[�vClass
//!
//! @details ���X�e�[�g�̃��[�vClass
//************************************************************
class NeedleState_Loop : public Needle::State
{
//====================
// �萔
//====================
private:
	static const Vec3 CENTER_POSITION;			//!< ���S����̍��W
	static const float ROTATION_CENTER_SPEED;	//!< ���S�̉�]���x
	static const float ROTATION_SPEED;			//!< ��]���x


//====================
// �ϐ�
//====================
private:
	Transform rotation_transform_;	//!<  ��]�p�ό`


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;
};



#endif