//================================================================================
//!	@file	 Collision.h
//!	@brief	 �󔒏Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COLLISION_NULL_H_
#define _COLLISION_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionBase.h"



//************************************************************														   
//! @brief   �󔒏Փ�Class
//!
//! @details �Փ˂̋�Class
//************************************************************
class CollisionNull : public CollisionBase
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionNull();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() override;

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() override;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() override;

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @details
	//! @param *information �Փˏ��
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionInformation* information) override;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) override;
};



#endif