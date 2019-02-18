//================================================================================
//!	@file	 CollisionBase.cpp
//!	@brief	 衝突BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../CollisionBase.h"



//****************************************
// プロパティ定義
//****************************************
CollisionBase::Type CollisionBase::getType()
{
	return type_;
}



void CollisionBase::setType(CollisionBase::Type value)
{
	type_ = value;
}



unsigned CollisionBase::getEndIndexOfArray()
{
	return collision_object_.getEndIndex();
}



CollisionObject* CollisionBase::getpCollisionObject(unsigned index)
{
	return collision_object_.getObject(index);
}



bool CollisionBase::getIsJudgement()
{
	bool is_judgement = false;
	for (unsigned i = 0; i < collision_object_.getEndIndex(); i++)
	{
		is_judgement = collision_object_.getObject(i)->getIsJudgement();
	}
	return is_judgement;
}



void CollisionBase::setIsJudgement(bool value)
{
	for (unsigned i = 0; i < collision_object_.getEndIndex(); i++)
	{
		collision_object_.getObject(i)->setIsJudgement(value);
	}
}



bool CollisionBase::getIsJudgmentGround()
{
	return is_judgment_ground_;
}



void CollisionBase::setIsJudgmentGround(bool value)
{
	is_judgment_ground_ = value;
}



//****************************************
// 関数定義
//****************************************
CollisionBase::~CollisionBase()
{
}



void CollisionBase::AddCollisionObject(CollisionObject* object)
{
	collision_object_.AddToArray(object);
}



void CollisionBase::OverwriteCollisionsObject(CollisionObject* old_object,
											  CollisionObject* new_object)
{
	old_object->ReleaseAllShape();
	collision_object_.OverwriteArray(old_object, new_object);
}



void CollisionBase::ReleaseCollisionObject(CollisionObject* object)
{
	object->ReleaseAllShape();
	collision_object_.DeleteFromArrayAndSort(object);
}



void CollisionBase::ReleaseAllCollisionObject()
{
	for (unsigned i = 0; i < collision_object_.getEndIndex(); i++)
	{
		collision_object_.getObject(i)->ReleaseAllShape();
	}
	collision_object_.ReleaseObjectAndReset();
}


void CollisionBase::UpdateAllCollisionObject()
{
	for (unsigned i = 0; i < collision_object_.getEndIndex(); i++)
	{
		collision_object_.getObject(i)->Update();
	}
}