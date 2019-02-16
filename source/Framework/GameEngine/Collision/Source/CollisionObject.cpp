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
const int CollisionObject::TAG_NONE = -1;



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



void CollisionObject::Init(int tag, CollisionBase* collision)
{
	tag_ = tag;
	collision_base_ = collision;
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
		Shape* shape = all_shape_.getObject(i);
		all_shape_.DeleteFromArrayAndSort(shape);
		SafeRelease::PlusUninit(&shape);
		return;
	}
}



void CollisionObject::ReleaseAllShape()
{
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		Shape* shape = all_shape_.getObject(i);
		SafeRelease::PlusUninit(&shape);
	}
	all_shape_.Reset();
}



void CollisionObject::UpdateAABB()
{
	Vector3D max;
	Vector3D min;
	for (unsigned i = 0; i < all_shape_.getEndIndex(); i++)
	{
		Vector3D temp_max = *all_shape_.getObject(i)->getpShape()->getpMax();
		Vector3D temp_min = *all_shape_.getObject(i)->getpShape()->getpMin();

		// 最小が上、最大が下の場合
		if (temp_min.y >= temp_max.y)
		{
			temp_max.y = -temp_max.y;
			temp_min.y = -temp_min.y;
		}
		// 最小が奥、最大が手前の場合
		if (temp_min.z >= temp_max.z)
		{
			temp_max.z = -temp_max.z;
			temp_min.z = -temp_min.z;
		}
		
		if (max.x < temp_max.x) max.x = temp_max.x;
		if (max.y < temp_max.y) max.y = temp_max.y;
		if (max.z < temp_max.z) max.z = temp_max.z;
		
		if (min.x > temp_min.x) min.x = temp_min.x;
		if (min.y > temp_min.y) min.y = temp_min.y;
		if (min.z > temp_min.z) min.z = temp_min.z;
	}

	*octree_aabb_.getpMax() = max;
	*octree_aabb_.getpMin() = min;
}