//================================================================================
//!	@file	 CollisionObjects.cpp
//!	@brief	 衝突オブジェクト群Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CollisionObjects.h"



//****************************************
// プロパティ定義
//****************************************
unsigned CollisionObjects::getEndIndexOfArray()
{
	return collision_object_.getEndIndex();
}



CollisionObject* CollisionObjects::getpCollisionObject(unsigned index)
{
	return collision_object_.getObject(index);
}



CollisionBase* CollisionObjects::getpCollisionBase()
{
	return collision_base_;
}



void CollisionObjects::setCollisionBase(CollisionBase* value)
{
	collision_base_ = value;
}



ObjectOfTree<CollisionObjects*>* CollisionObjects::getpObjectOfTree()
{
	return object_of_tree_;
}



void CollisionObjects::setObjectOfTree(ObjectOfTree<CollisionObjects*>* value)
{
	object_of_tree_ = value;
}



AABB* CollisionObjects::getOctreeAABB()
{
	return &octree_aabb_;
}



bool CollisionObjects::getIsJudgment()
{
	return is_judgment_;
}



void CollisionObjects::setIsJudgment(bool value)
{
	is_judgment_ = value;
}



//****************************************
// 関数定義
//****************************************
void CollisionObjects::AddCollisionObjectToArray(CollisionObject* object)
{
	collision_object_.AddToArray(object);
}



void CollisionObjects::OverwriteArrayCollisionObject(CollisionObject* old_object,
													 CollisionObject* new_object)
{
	collision_object_.OverwriteArray(old_object, new_object);
}



void CollisionObjects::ReleaseCollisionObjectFromArray(CollisionObject* object)
{
	collision_object_.DeleteFromArrayAndSort(object);
}



void CollisionObjects::ReleaseAllCollisionObjectFromArray()
{
	collision_object_.ReleaseObjectAndReset();
}



void CollisionObjects::ResetHitDataAllCollisionObject()
{
	for (unsigned i = 0; i < collision_object_.getEndIndex(); i++)
	{
		collision_object_.getObject(i)->ResetHitData();
	}
}