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
#include "../CollisionBase/CollisionBase.h"



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
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() override;

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object) override;

	//----------------------------------------
	//! @brief ��Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object) override;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) override;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̔�Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitGround(float position_y) override;
};



#endif