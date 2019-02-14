//================================================================================
//!	@file	 CollisionObject.cpp
//!	@brief	 衝突オブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CollisionObject.h"

#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const int CollisionObject::Shape::TAG_NONE = -1;



//****************************************
// プロパティ定義
//****************************************
int	CollisionObject::Shape::getTag()
{ 
	return tag_; 
}



CollisionShapeBase* CollisionObject::Shape::getpShape()
{ 
	return shape_; 
}



void CollisionObject::Shape::setShape(CollisionShapeBase* value)
{
	shape_ = value;
}



int	CollisionObject::getTag()
{
	return tag_;
}



unsigned CollisionObject::getEndIndexOfArray()
{
	return all_shape_.getEndIndex();
}



CollisionObject::Shape* CollisionObject::getpShape(unsigned index)
{
	return all_shape_.getObject(index);
}



CollisionBase* CollisionObject::getpCollisionBase()
{
	return collision_base_;
}



void CollisionObject::setCollisionBase(CollisionBase* value)
{
	collision_base_ = value;
}



ObjectOfTree<CollisionObject*>* CollisionObject::getpObjectOfTree()
{
	return object_of_tree_;
}



void CollisionObject::setObjectOfTree(ObjectOfTree<CollisionObject*>* value)
{
	object_of_tree_ = value;
}



AABB* CollisionObject::getOctreeAABB()
{
	return &octree_aabb_;
}



//****************************************
// 関数定義
//****************************************
void CollisionObject::Shape::Init(int tag, CollisionShapeBase* shape)
{
	tag_ = tag;
	shape_ = shape;
}



void CollisionObject::Shape::Uninit()
{
	SafeRelease::Normal(&shape_);
}



void CollisionObject::Init(int tag)
{
	tag_ = tag;
}



void CollisionObject::Update()
{
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		all_shape_.getObject(i)->getpShape()->Update();
	}
	UpdateAABB();
}



void CollisionObject::AddShape(int tag, CollisionShapeBase* shape)
{
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		if (all_shape_.getObject(i)->getTag() == tag) return;
	}
	CollisionObject::Shape* object_shape = new CollisionObject::Shape();
	object_shape->Init(tag, shape);
	all_shape_.AddToArray(object_shape);
}



void CollisionObject::ReleaseShape(int tag)
{
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		if (all_shape_.getObject(i)->getTag() != tag) continue;
		all_shape_.DeleteFromArrayAndSort(all_shape_.getObject(i));
		return;
	}
}



void CollisionObject::ReleaseAllShape()
{
	all_shape_.ReleaseObjectAndReset();
}



void CollisionObject::UpdateAABB()
{
	Vector3D min;
	Vector3D max;
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		Vec3 temp_min = *all_shape_.getObject(i)->getpShape()->getpMin();
		Vec3 temp_max = *all_shape_.getObject(i)->getpShape()->getpMax();

		// 最小が上、最大が下の場合
		if (temp_min.y >= temp_max.y)
		{
			temp_min.y = -temp_min.y;
			temp_max.y = -temp_max.y;
		}
		if (min < temp_min) min = temp_min;
		if (max > temp_max) max = temp_max;
	}

	octree_aabb_.setLength(max - min);
	octree_aabb_.Update();
}