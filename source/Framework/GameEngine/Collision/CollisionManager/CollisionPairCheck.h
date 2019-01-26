//================================================================================
//!	@file	 CollisionPairCheck.h
//!	@brief	 �Փ˃y�A����Class
//! @details static
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_COLLISION_PAIR_CHECK_H_
#define _COLLISION_PAIR_CHECK_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include <Component/Collision/CollisionBase/CollisionBase.h>

#include <Vector3D.h>



//************************************************************														   
//! @brief   �Փ˃y�A����Class(static)
//!
//! @details �Փˊ��N���X�̃y�A�𔻒肷��Class(static)
//************************************************************
class CollisionPairCheck
{
//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �Փˊ��N���X�y�A����֐�
	//! @details
	//! @param *collision0 �Փˊ��N���X
	//! @param *collision1 �Փˊ��N���X
	//! @retval bool �Փ˂��Ă����y�A�Ȃ�true
	//----------------------------------------
	static bool IsCheck(CollisionBase* collision0, CollisionBase* collision1);


private:
	//----------------------------------------
	//! @brief �y�A����֐�
	//! @details
	//! @param *collision0 �Փˊ��N���X
	//! @param *collision1 �Փˊ��N���X
	//! @retval bool �Փ˂��Ă����y�A�Ȃ�true
	//----------------------------------------
	static bool IsPair(CollisionBase* collision0, CollisionBase* collision1);

	//----------------------------------------
	//! @brief �w�肵���Փ˃^�C�v�̌����֐�
	//! @details
	//! @param type        �Փˊ��N���X�^�C�v
	//! @param *collision0 �Փˊ��N���X
	//! @param *collision1 �Փˊ��N���X
	//! @retval CollisionBase* �������ʂɍ��v�����Փˊ��N���X
	//----------------------------------------
	static CollisionBase* IsType(CollisionBase::Type type,
								  CollisionBase* collision0,
								  CollisionBase* collision1);

	//----------------------------------------
	//! @brief �w�肵���R���|�[�l���g�̋t��Ԃ��֐�
	//! @details
	//! @param *age_component �w�肷��Փˊ��N���X
	//! @param *collision0    �Փˊ��N���X
	//! @param *collision1    �Փˊ��N���X
	//! @retval CollisionBase* �w�肵���Փˊ��N���X�|�C���^�̋t�̏Փˊ��N���X
	//----------------------------------------
	static CollisionBase* OtherSideComponent(CollisionBase* age_component,
											 CollisionBase* collision0,
											 CollisionBase* collision1);

	//----------------------------------------
	//! @brief �v���C���[�̃y�A���X�g�֐�
	//! @details
	//! @param *collision �Փˊ��N���X
	//! @retval bool �Փ˂��Ă����y�A�Ȃ�true
	//----------------------------------------
	static bool PairList_Player(CollisionBase* collision);


//====================
// �����ς݊֐�
//====================
private:
	CollisionPairCheck() = delete;
	CollisionPairCheck(const CollisionPairCheck& value) = delete;
	CollisionPairCheck& operator = (const CollisionPairCheck& value) = delete;
};



#endif