//================================================================================
//!	@file	 CollisionPairCheck.cpp
//!	@brief	 �Փ˃y�A����Class
//! @details static
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionPairCheck.h"



//****************************************
// static�֐���`
//****************************************
bool CollisionPairCheck::IsCheck(CollisionBase* collision0, CollisionBase* collision1)
{
	if (!IsPair(collision0, collision1)) return false;

	return true;
}



bool CollisionPairCheck::IsPair(CollisionBase* collision0, CollisionBase* collision1)
{
	// �w�肵���R���|�[�l���g���i�[����
	CollisionBase* temp;

	// ������v���C���[�̏ꍇ
	temp = IsType(CollisionBase::Type::PLAYER, collision0, collision1);
	temp = OtherSideComponent(temp, collision0, collision1);

	if (temp != nullptr) return PairList_Player(temp);

	return false;
}



CollisionBase* CollisionPairCheck::IsType(CollisionBase::Type type,
										   CollisionBase* collision0,
										   CollisionBase* collision1)
{
	if (type == collision0->getType()) return collision0;
	if (type == collision1->getType()) return collision1;

	return nullptr;
}



CollisionBase* CollisionPairCheck::OtherSideComponent(CollisionBase* age_component,
													  CollisionBase* collision0,
													  CollisionBase* collision1)
{
	if (age_component == nullptr) return nullptr;
	if (age_component == collision0) return collision1;
	if (age_component == collision1) return collision0;

	return nullptr;
}



bool CollisionPairCheck::PairList_Player(CollisionBase* collision)
{
	switch (collision->getType())
	{
		// �Փ˂������Ȃ��Փ˃R���|�[�l���g
		case CollisionBase::Type::PLAYER:
		{
			return false;
		}
	}

	return true;
}